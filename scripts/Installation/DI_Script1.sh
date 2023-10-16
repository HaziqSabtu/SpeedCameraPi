#!/bin/bash
set -e
# This script updates package information, upgrades packages, and modifies dphys-swapfile configuration

# Check if script is run with sudo
if [ "$EUID" -ne 0 ]; then
  echo "Please run this script with sudo or as root."
  exit 1
fi

echo "********************************************************************"
echo "Dependency Installation Script 1"
echo ""
echo ""

# Explanation of script actions
echo "This script will perform the following actions:"
echo "1. Update package information."
echo "2. Upgrade packages."
echo "3. Modify dphys-swapfile configuration to set CONF_SWAPSIZE and CONF_MAXSWAP to 4096."
echo

# Prompt for confirmation
read -p "Do you want to proceed? (y/n): " choice
if [ "$choice" != "y" ]; then
  echo "Script execution aborted."
  exit 0
fi

# Run apt-get update
sudo apt-get update

# Run apt-get upgrade
sudo apt-get upgrade

# Define the new CONF_SWAPSIZE value
NEW_SWAPSIZE=4096

# Update CONF_SWAPSIZE in dphys-swapfile configuration
sudo sed -i "s/CONF_SWAPSIZE=.*/CONF_SWAPSIZE=$NEW_SWAPSIZE/" /etc/dphys-swapfile

# Update CONF_MAXSWAP in dphys-swapfile configuration
sudo sed -i "s/CONF_MAXSWAP=.*/CONF_MAXSWAP=$NEW_SWAPSIZE/" /sbin/dphys-swapfile

# Restart dphys-swapfile service
sudo systemctl restart dphys-swapfile

echo "Script executed successfully."
echo "Please reboot for changes to take effect"
echo "Run DI_Script2.sh to proceed with installation after reboot"