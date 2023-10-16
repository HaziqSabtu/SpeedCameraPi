#!/bin/bash
set -e

# Check if script is run with sudo
if [ "$EUID" -ne 0 ]; then
  echo "Please run this script with sudo or as root."
  exit 1
fi

echo "********************************************************************"
echo "Dependency Installation Script 4"
echo ""
echo ""
echo
# Explanation of script actions
echo "This script will perform the following actions:"
echo "1. Install libcamera v0.0.4"
echo
echo "It will take minimal 1.0 hour !"
echo
echo ""

# Prompt for confirmation
read -p "Do you want to proceed? (y/n): " choice
if [ "$choice" != "y" ]; then
  echo "Script execution aborted."
  exit 0
fi

# Update and upgrade packages
sudo apt-get update && sudo apt-get upgrade

# Install required dependencies
sudo apt install -y libboost-dev
sudo apt install -y libgnutls28-dev openssl libtiff5-dev pybind11-dev
sudo apt install -y qtbase5-dev libqt5core5a libqt5gui5 libqt5widgets5
sudo apt install -y meson
sudo apt install -y cmake
sudo pip3 install pyyaml ply
sudo pip3 install --upgrade meson

sudo apt install -y libglib2.0-dev libgstreamer-plugins-base1.0-dev


# Download libcamera
cd
git clone https://github.com/raspberrypi/libcamera.git
cd libcamera
git checkout v0.0.4

# Configure the build process
meson build --buildtype=release -Dpipelines=raspberrypi -Dipas=raspberrypi -Dv4l2=true -Dgstreamer=enabled -Dtest=false -Dlc-compliance=disabled -Dcam=disabled -Dqcam=enabled -Ddocumentation=disabled -Dpycamera=enabled

# Compile and install the library
ninja -C build -j2   # use -j 2 on Raspberry Pi 3 or earlier devices
sudo ninja -C build install

echo "libcamera v0.0.4 succesfully installed"
echo
echo
echo "Run DI_Script5.sh to proceed with installation"
