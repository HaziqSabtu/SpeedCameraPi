#!/usr/bin/env python3

import tarfile
import subprocess
import shutil
import os
import Ssymlinker as linker
import SyncwithTarget
import cUtils

# do not run with sudo
if cUtils.isRunningWithSudo():
    print("Please run this script without sudo.")
    exit()
    

# Step 1: Zip a folder with tar
def zip_folder(folder_path, output_tar):
    with tarfile.open(output_tar, 'w:gz') as tar:
        tar.add(folder_path, arcname='.')

# Step 2: Send the tar to target via SCP (SSH)
def send_tar_via_scp(output_tar, target_ip, target_path):
    scp_command = f'scp {output_tar} {target_ip}:{target_path}'
    os.system(scp_command)

# Step 3: Extract the tar on the target
def extract_tar_on_target(target_ip, target_path):
    ssh_command = f'ssh {target_ip} "sudo tar -xzf {target_path} -C /usr/"'
    os.system(ssh_command)

# Define paths and credentials
home_dir = os.path.expanduser("~")
cxcmpl_path = f'{home_dir}/cxcmpl'
lib_path = f'{cxcmpl_path}/cv'
output_tar = f'{cxcmpl_path}/cv.tar'
target_ip = 'RPi0'
target_path = '~/cv.tar'

# Step 1: Zip the folder
zip_folder(lib_path, output_tar)

# Step 2: Send the tar via SCP
send_tar_via_scp(output_tar, target_ip, target_path)

# Step 3: Extract the tar on the target
extract_tar_on_target(target_ip, target_path)

# Step 4: Fix the symlinks on the target
linker.check_and_download_ssymlinker()
linker.linkAll()

# Step 5: Sync the target with the host
SyncwithTarget.syncAll(cxcmpl_path)
