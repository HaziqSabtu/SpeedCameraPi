#!/usr/bin/env python3

import os
import argparse
import sys

def update_sources(credentials, password):
    commands = [
        'echo "deb-src http://raspbian.raspberrypi.org/raspbian/ buster main contrib non-free rpi" | sudo tee -a /etc/apt/sources.list',
        'sudo apt update',
        'sudo apt dist-upgrade',
        f'echo "$USER ALL=NOPASSWD:$(which rsync)" | sudo tee --append /etc/sudoers',
        'sudo apt install build-essential cmake unzip pkg-config gfortran gcc g++ gperf flex texinfo gawk bison openssl pigz libncurses-dev autoconf automake tar figlet'
    ]

    for command in commands:
        os.system(f'ssh {credentials} "{command}"')

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Update sources.list and perform system upgrades on a Raspberry Pi Zero over SSH")
    parser.add_argument("credentials", help="Username and IP address in the format 'username@ip_address'")
    parser.add_argument("password", help="Password for SSH login")

    args = parser.parse_args()

    if len(sys.argv) != 3:
        parser.print_usage()
        sys.exit(1)

    update_sources(args.credentials, args.password)