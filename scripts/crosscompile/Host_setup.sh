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
sudo -u $SUDO_USER mkdir /home/$SUDO_USER/cxcmpl
sudo -u $SUDO_USER mkdir /home/$SUDO_USER/cxcmpl/tools
sudo -u $SUDO_USER mkdir /home/$SUDO_USER/cxcmpl/build
sudo -u $SUDO_USER mkdir /home/$SUDO_USER/cxcmpl/sysroot
sudo -u $SUDO_USER mkdir /home/$SUDO_USER/cxcmpl/sysroot/usr
sudo -u $SUDO_USER mkdir /home/$SUDO_USER/cxcmpl/sysroot/opt
sudo -u $SUDO_USER chown -R 1000:1000 /home/$SUDO_USER/cxcmpl

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
sudo -u $SUDO_USER chmod +x /home/$SUDO_USER/cxcmpl/sysroot-relativelinks.py

cp PI.cmake ~/cxcmpl/tools/PI.cmake

echo "All required packages have been installed"