#!/usr/bin/env python3

import os
import json

# Get the current username
username = os.getlogin()

# Define the configurations
configurations = [
    {
        "name": "(GDB-Auto) Remote GDB Launch",
        "type": "cppdbg",
        "request": "launch",
        "program": "${command:cmake.launchTargetPath}",
        "args": [],
        "cwd": "${workspaceRoot}",
        "preLaunchTask": "startGDB",
        "postDebugTask": "killGDB",
        "environment": [],
        "setupCommands": [
            {
                "text": "target remote 192.168.178.45:2000",
                "description": "Target",
                "ignoreFailures": false
            },
            {
                "description": "Test",
                "text": "python import sys;sys.path.insert(0, '/usr/share/gcc/python');from libstdcxx.v6.printers import register_libstdcxx_printers;register_libstdcxx_printers(None)",
                "ignoreFailures": false
            },
            {
                "text": "-enable-pretty-printing",
                "description": "Enable GDB pretty printing",
                "ignoreFailures": false
            },
            {
                "description": "Set sysroot directory",
                "text": "set sysroot /home/username/cxcmpl/sysroot",
                "ignoreFailures": true
            },
            {
                "text": "skip -rfu ^std::.*",
                "description": "Don't step into standard library ",
                "ignoreFailures": false
            },
            {
                "text": "skip -rfu ^cv::.*",
                "description": "Don't step into cv library ",
                "ignoreFailures": false
            },
        ],
        "stopAtEntry": true,
        "targetArchitecture": "arm",
        "miDebuggerPath": "/home/username/cxcmpl/tools/cross-pi-gcc-10.3.0-2/bin/arm-linux-gnueabihf-gdb",
        "MIMode": "gdb",
        "externalConsole": false,
        "sourceFileMap": {
            "${workspaceFolder}": {
                "editorPath": "${workspaceFolder}",
                "useForBreakpoints": "true"
            }
        },
        "logging": {
            "engineLogging": true
        }
    },
    {
        "name": "(GDB-Manual) Remote GDB Launch",
        "type": "cppdbg",
        "request": "launch",
        "program": "${command:cmake.launchTargetPath}",
        "args": [],
        "cwd": "${workspaceRoot}",
        "environment": [],
        "setupCommands": [
            {
                "text": "target remote 192.168.178.45:2000",
                "description": "Target",
                "ignoreFailures": false
            },
            {
                "text": "-enable-pretty-printing",
                "description": "Enable GDB pretty printing",
                "ignoreFailures": false
            },
            {
                "text": "skip -rfu ^std::.*",
                "description": "Don't step into standard library ",
                "ignoreFailures": false
            },
            {
                "text": "skip -rfu ^cv::.*",
                "description": "Don't step into cv library ",
                "ignoreFailures": false
            },
        ],
        "stopAtEntry": true,
        "targetArchitecture": "arm",
        "miDebuggerPath": "/home/username/cxcmpl/tools/cross-pi-gcc-10.3.0-2/bin/arm-linux-gnueabihf-gdb",
        "MIMode": "gdb",
        "externalConsole": false,
        "sourceFileMap": {
            "${workspaceFolder}": {
                "editorPath": "${workspaceFolder}",
                "useForBreakpoints": "true"
            }
        },
        "logging": {
            "engineLogging": true
        }
    }
]

# Create the JSON structure
json_data = {
    "version": "0.2.0",
    "configurations": configurations
}

# Replace the username in the setupCommands
for config in json_data["configurations"]:
    for command in config.get("setupCommands", []):
        if "text" in command and "home/username" in command["text"]:
            command["text"] = command["text"].replace("home/username", f"home/{username}")

# Write to the JSON file
with open("launch.json", "w") as json_file:
    json.dump(json_data, json_file, indent=4)

print("Generated launch.json with updated username.")
