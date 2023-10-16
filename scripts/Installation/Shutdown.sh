#!/bin/bash

echo "************************************************************************"
echo ""
echo "This script will generate two scripts that will allow you to shutdown"
echo "and reboot the system. The scripts will be placed on the desktop."
echo ""
echo "************************************************************************"
# Define the names of the generated scripts
shutdown_script="shutdown.sh"
reboot_script="reboot.sh"

# Define the desktop directory
desktop_dir="$HOME/Desktop"

# Create the shutdown script
cat <<EOL > "$shutdown_script"
#!/bin/bash

shutdown -h now
EOL

# Make the shutdown script executable
chmod +x "$shutdown_script"

# Create the reboot script
cat <<EOL > "$reboot_script"
#!/bin/bash

reboot
EOL

# Make the reboot script executable
chmod +x "$reboot_script"

# Move the scripts to the desktop
mv "$shutdown_script" "$reboot_script" "$desktop_dir/"

echo "Generated scripts '$shutdown_script' and '$reboot_script' placed on the desktop."
