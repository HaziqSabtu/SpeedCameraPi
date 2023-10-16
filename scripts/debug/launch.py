#!/usr/bin/env python3

import os
import json
import sys
import re
import shutil

def is_valid_ip(ip):
    # Define a regular expression pattern for a valid IP address
    pattern = r'^\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}$'
    return re.match(pattern, ip) is not None

def update_json(ip_address):
    if ip_address.lower() == "raspberrypi":
        print("Error: 'raspberrypi' cannot be used as an IP address.")
        return

    if not is_valid_ip(ip_address):
        print("Invalid IP address format. Please provide a valid IP address.")
        return

    # Get the current username
    username = os.getlogin()

    # Define the path to the launch.json file
    file_path = "./launch.json"

    # Check if the file exists
    if os.path.exists(file_path):
        # Read the content of the file
        with open(file_path, 'r') as file:
            data = json.load(file)

        # Replace the username in the setupCommands and IP address
        for config in data["configurations"]:
            for command in config.get("setupCommands", []):
                if "text" in command and "home/haziqsabtu" in command["text"]:
                    command["text"] = command["text"].replace("home/haziqsabtu", f"home/{username}")

                if "target remote 192.168.178.45:2000" in command.get("text", ""):
                    command["text"] = command["text"].replace("192.168.178.45", ip_address)

            if "miDebuggerPath" in config and "home/haziqsabtu" in config["miDebuggerPath"]:
                config["miDebuggerPath"] = config["miDebuggerPath"].replace("home/haziqsabtu", f"home/{username}")

        # Write the updated content back to the file
        with open(file_path, 'w') as file:
            json.dump(data, file, indent=4)

        print(f"Updated launch.json with current OS user and IP: {ip_address}.")

        # Copy the updated launch.json to .vscode directory
        shutil.copy(file_path, "../../.vscode/launch.json")
        print("Copied launch.json to .vscode directory.")
    else:
        print(f"The file {file_path} does not exist.")

# Check if the IP address was provided as a command line argument
if len(sys.argv) < 2:
    print("Usage: python3 script.py <ip_address>")
    sys.exit(1)

# Get the IP address from the command line argument
ip_address = sys.argv[1]

# Call the function to update the JSON
update_json(ip_address)
