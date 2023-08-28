#!/bin/bash

echo "************************************************************************"
echo ""
echo "Touchscreen rotation Script"
echo "credit: https://www.waveshare.com/w/upload/5/58/7inch_HDMI_LCD_(H)_User_Manual.pdf"
echo ""
echo "************************************************************************"

# Check if the script is being run with root privileges
if [ "$EUID" -ne 0 ]; then
  echo "Please run this script as root."
  exit 1
fi

# Update the package list
sudo apt-get update
sudo apt-get upgrade -y

# rotate screen
cat << EOF >> /boot/config.txt
max_usb_current=1
hdmi_force_hotplug=1
config_hdmi_boost=10
hdmi_group=2
hdmi_mode=87
hdmi_cvt 1024 600 60 6 0 0 0
display_rotate=1
EOF

# prevent overriding
sudo sed -i "s/dtoverlay=vc4-kms-v3d/# dtoverlay=vc4-kms-v3d/" /boot/config.txt
# sudo sed -i "s/dtoverlay=vc4-fkms-v3d/# dtoverlay=vc4-fkms-v3d/" /boot/config.txt

# rotate touchscreen
sudo apt-get install xserver-xorg-input-libinput

# check if folder is exist
if [ ! -d "/etc/X11/xorg.conf.d" ]; then
  sudo mkdir /etc/X11/xorg.conf.d
fi

sudo cp /usr/share/X11/xorg.conf.d/40-libinput.conf /etc/X11/xorg.conf.d/

# sudo nano /etc/X11/xorg.conf.d/40-libinput.conf



# Define the content to search for
search_content='Section "InputClass"
        Identifier "libinput touchscreen catchall"
        MatchIsTouchscreen "on"
        MatchDevicePath "/dev/input/event*"
        Driver "libinput"
EndSection'

# Define the new content to replace with
new_content='Section "InputClass"
        Identifier "libinput touchscreen catchall"
        MatchIsTouchscreen "on"
        Option "CalibrationMatrix" "0 1 0 -1 0 1 0 0 1"
        MatchDevicePath "/dev/input/event*"
        Driver "libinput"
EndSection'

# File path
file_path="/etc/X11/xorg.conf.d/40-libinput.conf"

# Use awk to replace content
awk -v search="$search_content" -v replace="$new_content" 'BEGIN { RS = "" } $0 == search { print replace; found = 1 } END { if (!found) { print "Search content not found in the file."; exit 1 } }' "$file_path" > "$file_path.tmp"

# Replace the original file with the modified content
mv "$file_path.tmp" "$file_path"

echo "Content replaced successfully."


echo ""
echo ""
echo "" Success! Reboot to apply changes
echo ""
echo ""
echo "******************************************************************************************************"