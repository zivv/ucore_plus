#!/bin/bash

# transfer ./kernel.img to SD card

while :
do
    SDloaded=`ls /Volumes | grep boot`
    if [ "$SDloaded" == "boot" ]; then
        cp kernel.img /Volumes/boot
        umount /Volumes/boot
        break
    fi
done
echo "dd to /Volumes/boot"
