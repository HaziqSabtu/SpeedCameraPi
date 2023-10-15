#!/usr/bin/env python3

import subprocess
import os
import shutil

# do not run with sudo

def copy_if_not_exists(source, destination):
    if not os.path.exists(destination):
        shutil.copyfile(source, destination)
        print(f"Copied {source} to {destination}")

def syncAll(cxcmpl_dir):
    commands = [
        f'rsync -avz --rsync-path="sudo rsync" --delete RPi0:/lib {cxcmpl_dir}/sysroot',
        f'rsync -avz --rsync-path="sudo rsync" --delete RPi0:/usr/include {cxcmpl_dir}/sysroot/usr',
        f'rsync -avz --rsync-path="sudo rsync" --delete RPi0:/usr/lib {cxcmpl_dir}/sysroot/usr',
        f'rsync -avz --rsync-path="sudo rsync" --delete RPi0:/usr/local {cxcmpl_dir}/sysroot/usr',
        f'./sysroot-relativelinks.py {cxcmpl_dir}/sysroot'
    ]
    for command in commands:
        subprocess.run(command, shell=True)