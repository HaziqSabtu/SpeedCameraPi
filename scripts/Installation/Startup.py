#!/usr/bin/env python3

import os
import subprocess
import shutil

print("************************************************************************")
print()
print("This script will perform the following actions:")
print(" 1. Create a bash script to run the executable at startup")
print(" 2. Create a systemd service file to run the bash script at startup")
print(" 3. Update the LXPanel configuration to autohide taskbar")
print()
print("************************************************************************")


def main():
    if os.geteuid() == 0:
        # Running with sudo

        # Get the regular user's home directory
        sudo_user = os.getenv("SUDO_USER")
        regular_user_home = os.path.expanduser(f"~{sudo_user}")

        auto_script = os.path.join(regular_user_home, "auto.sh")

        with open(auto_script, "w") as f:
            f.write(
                '''#!/bin/bash

# Define the executable name
executable_name="SpeedCameraPi"

# Define the user's home directory
user_home="'''
                + regular_user_home
                + """"

# Check if the executable exists in the user's build directory
if [ -x "$user_home/SpeedCameraPi/build/$executable_name" ]; then
    # Change to the build directory
    cd "$user_home/SpeedCameraPi/build"
    # Run the executable
    "./$executable_name"
# Check if the executable exists in the user's Target directory
elif [ -x "$user_home/Target/$executable_name" ]; then
    # Change to the Target directory
    cd "$user_home/Target"
    # Run the executable
    "./$executable_name"
else
    echo "Executable not found in both locations."
    exit 1
fi
"""
            )

        # Make the script executable
        os.chmod(auto_script, 0o755)

        print(f"Script created successfully: {auto_script}")

        # Create systemd service file
        service_file = "/etc/systemd/user/scp.service"
        with open(service_file, "w") as f:
            f.write(
                """[Unit]
Description=My Application Startup
After=default.target

[Service]
ExecStart="""
                + os.path.join(regular_user_home, "auto.sh")
                + """
KillSignal=SIGINT

[Install]
WantedBy=default.target
"""
            )

        # Update LXPanel configuration
        lxpanel_config_path = "/etc/xdg/lxpanel/LXDE-pi/panels/panel"
        shutil.move(lxpanel_config_path, lxpanel_config_path + ".bak")
        with open(lxpanel_config_path + ".bak", "r") as infile:
            with open(lxpanel_config_path, "w") as outfile:
                for line in infile:
                    if "autohide=" in line:
                        outfile.write("autohide=1\n")
                    elif "heightwhenhidden=" in line:
                        outfile.write("heightwhenhidden=0\n")
                    else:
                        outfile.write(line)

        print("LXPanel configuration updated.")

        print("Please run --> systemctl --user enable scp.service <-- from terminal")

    else:
        # Not running with sudo
        print("Please run this script with sudo.")
        exit(1)


if __name__ == "__main__":
    main()
