#!/usr/bin/env python3

import subprocess
import sys

# do not run with sudo

def setup_ssh_key(hostname, user):
    # Generate SSH key pair
    subprocess.run(['ssh-keygen'])

    # Add host configuration to SSH config file
    ssh_config = f'''
Host RPi0
    HostName {hostname}
    User {user}
'''
    with open(f'{home_dir}/.ssh/config', 'a') as config_file:
        config_file.write(ssh_config)

    # Copy public key to remote host
    subprocess.run(['ssh-copy-id', '-i', f'{home_dir}/.ssh/id_rsa.pub', 'RPi0'])

# Get the home directory
home_dir = os.path.expanduser("~")

# Check if hostname and user were provided as arguments
if len(sys.argv) != 3:
    print("Usage: python3 setup_ssh.py <hostname> <user>")
    sys.exit(1)

# Extract hostname and user from arguments
hostname = sys.argv[1]
user = sys.argv[2]

# Call the function
setup_ssh_key(hostname, user)