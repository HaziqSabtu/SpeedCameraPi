#!/bin/bash

# credit: https://variwiki.com/index.php?title=Yocto_Programming_with_VSCode&release=RELEASE_DUNFELL_V1.3_VAR-SOM-MX8X
readonly PROGRAM="./SpeedCameraPi"
readonly TARGET_DIR="~/Target"


# Must match startsPattern in tasks.json
echo "Deploying to target"

# Must match endsPattern in tasks.json
echo "Starting GDB Server on Target"

# start gdbserver on target
 ssh -Y RPi0 "sh -c 'cd ${TARGET_DIR}; DISPLAY=:0 nohup gdbserver localhost:2000 ${PROGRAM}'"