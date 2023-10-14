#!/bin/bash

# Update package lists
sudo apt update

# Upgrade packages
sudo apt dist-upgrade -y

# Install required packages
sudo apt install -y build-essential cmake unzip gfortran
sudo apt install -y gcc git bison python gperf pkg-config gdb-multiarch wget rsync
sudo apt install -y g++ gperf flex texinfo gawk bison openssl pigz libncurses-dev autoconf automake tar figlet

# Create directories and set permissions
sudo mkdir ~/cxcmpl
sudo mkdir ~/cxcmpl/tools
sudo mkdir ~/cxcmpl/build
sudo mkdir ~/cxcmpl/sysroot
sudo mkdir ~/cxcmpl/sysroot/usr
sudo mkdir ~/cxcmpl/sysroot/opt
sudo chown -R 1000:1000 ~/cxcmpl

# Change directory to cxcmpl
cd ~/cxcmpl

# Download cross-gcc-10.3.0-pi_3+ toolchain
cd ~/cxcmpl/tools
wget https://sourceforge.net/projects/raspberry-pi-cross-compilers/files/Raspberry%20Pi%20GCC%20Cross-Compiler%20Toolchains/Bullseye/GCC%2010.3.0/Raspberry%20Pi%203A%2B%2C%203B%2B%2C%204/cross-gcc-10.3.0-pi_3%2B.tar.gz

# Extract the downloaded tarball
tar xf cross-gcc-*.tar.gz

# Copy sysroot-relativelinks.py
cp sysroot-relativelinks.py ~/cxcmpl/sysroot-relativelinks.py

# Make sysroot-relativelinks.py executable
sudo chmod +x ~/cxcmpl/sysroot-relativelinks.py

cp PI.cmake ~/cxcmpl/tools/PI.cmake

echo "All required packages have been installed, directories set up, the toolchain downloaded and extracted, sysroot-relativelinks.py has been copied, and it is now executable."
