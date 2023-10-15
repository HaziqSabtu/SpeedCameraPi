#!/usr/bin/env python3

import os
import argparse
import sys
import Host_syncWithTarget as sync
import cUtils

# do not run with sudo
if cUtils.isRunningWithSudo():
    print("Do not run with sudo")
    sys.exit(1)

def update_sources(credentials):
    commands = [
        'sudo apt-get install -y build-essential cmake git unzip pkg-config'
        'sudo apt-get install -y libjpeg-dev libtiff-dev libpng-dev'
        'sudo apt-get install -y libavcodec-dev libavformat-dev libswscale-dev'
        'sudo apt-get install -y libgtk2.0-dev libcanberra-gtk* libgtk-3-dev'
        'sudo apt-get install -y libgstreamer1.0-dev gstreamer1.0-gtk3'
        'sudo apt-get install -y libgstreamer-plugins-base1.0-dev gstreamer1.0-gl'
        'sudo apt-get install -y libxvidcore-dev libx264-dev'
        'sudo apt-get install -y python3-dev python3-numpy python3-pip'
        'sudo apt-get install -y libtbb2 libtbb-dev libdc1394-22-dev'
        'sudo apt-get install -y libv4l-dev v4l-utils'
        'sudo apt-get install -y libopenblas-dev libatlas-base-dev libblas-dev'
        'sudo apt-get install -y liblapack-dev gfortran libhdf5-dev'
        'sudo apt-get install -y libprotobuf-dev libgoogle-glog-dev libgflags-dev'
        'sudo apt-get install -y protobuf-compiler'
    ]

    for command in commands:
        os.system(f'ssh {credentials} "{command}"')

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Prepare Target for OpenCV installation")
    parser.add_argument("credentials", help="Username and IP address in the format 'username@ip_address'")

    args = parser.parse_args()

    if len(sys.argv) != 2:
        parser.print_usage()
        sys.exit(1)

    update_sources(args.credentials)

    home_dir = os.path.expanduser("~")
    cxcmpl_dir = os.path.join(home_dir, "cxcmpl")
    sync.syncAll(cxcmpl_dir)
