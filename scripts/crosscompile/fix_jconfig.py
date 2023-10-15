#!/usr/bin/env python3

import os
import Target_Ssymlinker

# do not run with sudo

# Check if SSymlinker executable exists on target
Target_Ssymlinker.check_and_download_ssymlinker()

# Define the SSH command
ssh_command = 'ssh RPi0 "cd ~ && ./SSymlinker -s /usr/include/arm-linux-gnueabihf/jconfig.h -d /usr/include/jconfig.h"'

# Execute the SSH command
os.system(ssh_command)
