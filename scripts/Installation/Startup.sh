#!/bin/bash

# NOT FINISHED

if [ "$EUID" = 0 ]; then
    # Running with sudo

    # Get the regular user's home directory
    regular_user_home="$(eval echo ~$SUDO_USER)"

    auto_script="$regular_user_home/auto.sh"

    cat << EOF > "$auto_script"
#!/bin/bash

# Define the executable name
executable_name="SpeedCameraPi"

# Define the user's home directory
user_home="$regular_user_home"

# Check if the executable exists in the user's build directory
if [ -x "\$user_home/SpeedCameraPi/build/\$executable_name" ]; then
    # Change to the build directory
    cd "\$user_home/SpeedCameraPi/build"
    # Run the executable
    "./\$executable_name"
# Check if the executable exists in the user's Target directory
elif [ -x "\$user_home/Target/\$executable_name" ]; then
    # Change to the Target directory
    cd "\$user_home/Target"
    # Run the executable
    "./\$executable_name"
else
    echo "Executable not found in both locations."
    exit 1
fi

EOF

    # Make the script executable
    chmod +x "$auto_script"

    echo "Script created successfully: $auto_script"

    auto_script="$regular_user_home/auto.sh"

cat << 'EOF' > /etc/systemd/user/scp.service
[Unit]
Description=My Application Startup
After=default.target

[Service]
ExecStart=/home/haziqsabtu/auto.sh
KillSignal=SIGINT

[Install]
WantedBy=default.target"
EOF

systemctl --user enable scp.service

sudo sed -i "s/autohide=.*/autohide=1/" /etc/xdg/lxpanel/LXDE-pi/panels/panel
sudo sed -i "s/heightwhenhidden=.*/heightwhenhidden=0/" /etc/xdg/lxpanel/LXDE-pi/panels/panel

else
    # Not running with sudo
    echo "Please run this script with sudo."
    exit 1
fi
