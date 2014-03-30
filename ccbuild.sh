#!/bin/bash

cd ucore

#rascleandefmake
#make clean
#make ARCH=arm BOARD=raspberrypi defconfig
make BOARD=raspberrypi sfsimg && make BOARD=raspberrypi kernel

cd ..
cd arm_raspi
make
cd ..
cp arm_raspi/kernel.img .

