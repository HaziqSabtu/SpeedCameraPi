#!/usr/bin/env python3

import os
import Ssymlinker as linker
import cUtils
import SyncWTarget as sync

# do not run with sudo
if cUtils.isRunningWithSudo():
    print("Do not run with sudo")
    sys.exit(1)

linker.check_and_download_ssymlinker()

# Define the SSH command
ssh_command = 'ssh RPi0 "cd ~ && ./SSymlinker -s /usr/include/arm-linux-gnueabihf/jconfig.h -d /usr/include/jconfig.h"'

# Execute the SSH command
os.system(ssh_command)

home_dir = os.path.expanduser("~")
cxcmpl_dir = os.path.join(home_dir, "cxcmpl")
sync.syncAll(cxcmpl_dir)
