obj-y := dde.o bcm2708.dummy.o bcm2708_fb.o

dirs-y := cfb

TARGET_CFLAGS += -D__KERNEL__ \
				 -D__KERN__ \
				 -DKBUILD_BASENAME=\"dde\" \
				 -DKBUILD_MODNAME=\"dde\" \
				 -D__LINUX_ARM_ARCH__ \
				 -I$(KTREE)/arch/arm/mach-raspberrypi\
				 -I$(KTREE)/arch/arm/mach-raspberrypi/linux_fb_drv\
				 -I$(KTREE)/arch/arm/mach-raspberrypi/linux_fb_drv/include\
				 -I$(KTREE)/arch/arm/mach-raspberrypi/linux_fb_drv/include/generated\
				 -I$(KTREE)/arch/arm/mach-raspberrypi/linux_fb_drv/include/uapi\
			   -include linux/kconfig.h
