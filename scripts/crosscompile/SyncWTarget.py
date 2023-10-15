#!/usr/bin/env python3

import subprocess
import os
import shutil

sysroot_fn = "sysroot-relativelinks.py"

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