#!/bin/bash

cd ucore

#rascleandefmake
make clean
make ARCH=arm BOARD=raspberrypi defconfig
make sfsimg && make kernel

cd ..
cd arm_raspi
make
cd ..
cp arm_raspi/kernel.img .

