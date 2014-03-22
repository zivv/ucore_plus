#!/bin/bash

# transfer ./kernel.img to SD card

cp kernel.img /Volumes/boot
umount /Volumes/boot
