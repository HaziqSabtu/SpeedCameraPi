#!/bin/bash
set -e

# Check if script is run with sudo
if [ "$EUID" -ne 0 ]; then
  echo "Please run this script with sudo or as root."
  exit 1
fi

echo "********************************************************************"
echo "Dependency Installation Script 3"
echo ""
echo ""
echo
# Explanation of script actions
echo "This script will perform the following actions:"
echo "1. Install wxWidgets v3.2.2.1"
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
sudo apt-get install libgtk-3-dev build-essential checkinstall

# Download wxWidgets
wget https://github.com/wxWidgets/wxWidgets/releases/download/v3.2.2.1/wxWidgets-3.2.2.1.tar.bz2

# Extract the downloaded archive
tar -xvf wxWidgets-3.2.2.1.tar.bz2

# Change directory to the extracted directory
cd wxWidgets-3.2.2.1

# Create build directory and navigate to it
mkdir gtk-build
cd gtk-build

# Configure the build process
../configure --disable-shared --enable-unicode --disable-debug

# Compile and install the library
make
sudo make install

# Optional: Clean up
# cd ../../   # Navigate back to the original directory
# rm wxWidgets-3.2.2.1.tar.bz2   # Remove downloaded archive

echo "wxWidgets v3.2.2.1 succesfully installed"
echo
echo
echo "Run DI_Script4.sh to proceed with installation"
