#!/usr/bin/env python3

import subprocess

def check_and_download_ssymlinker():
    # Define the SSH command to check if SSymlinker executable exists
    check_command = 'ssh RPi0 "[ -x ~/SSymlinker ] && echo 1 || echo 0"'

    # Execute the SSH command and capture the output
    result = subprocess.check_output(check_command, shell=True)

    # Decode the result to a string and interpret
    result = result.decode().strip()
    if result == '0':
        print("SSymlinker executable does not exist. Downloading...")
        download_command = 'ssh RPi0 "cd ~ && wget https://raw.githubusercontent.com/abhiTronix/raspberry-pi-cross-compilers/master/utils/SSymlinker"'
        subprocess.run(download_command, shell=True)

        print("Setting execute permissions...")
        chmod_command = 'ssh RPi0 "sudo chmod +x ~/SSymlinker"'
        subprocess.run(chmod_command, shell=True)
    else:
        print("SSymlinker executable already exists.")

def linkAll():
    link_commands = [
        './SSymlinker -s /usr/include/arm-linux-gnueabihf/asm -d /usr/include',
        './SSymlinker -s /usr/include/arm-linux-gnueabihf/gnu -d /usr/include',
        './SSymlinker -s /usr/include/arm-linux-gnueabihf/bits -d /usr/include',
        './SSymlinker -s /usr/include/arm-linux-gnueabihf/sys -d /usr/include',
        './SSymlinker -s /usr/include/arm-linux-gnueabihf/openssl -d /usr/include',
        './SSymlinker -s /usr/lib/arm-linux-gnueabihf/crtn.o -d /usr/lib/crtn.o',
        './SSymlinker -s /usr/lib/arm-linux-gnueabihf/crt1.o -d /usr/lib/crt1.o',
        './SSymlinker -s /usr/lib/arm-linux-gnueabihf/crti.o -d /usr/lib/crti.o'
    ]

    for command in link_commands:
        ssh_command = f'ssh RPi0 "cd ~ && {command}"'
        subprocess.run(ssh_command, shell=True)

check_and_download_ssymlinker()
linkAll()