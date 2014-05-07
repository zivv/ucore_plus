obj-y := dde.o bcm2708.dummy.o bcm2708_fb.o

dirs-y := cfb

TARGET_CFLAGS += -D__KERNEL__ \
				 -D__KERN__ \
				 -DKBUILD_BASENAME=\"dde\" \
			     -DKBUILD_MODNAME=\"dde\" \
			     -D__LINUX_ARM_ARCH__ \
				 -I/Users/cc/Documents/course/OS/UCORE/ucore_plus/ucore/src/kern-ucore/arch/arm/mach-raspberrypi\
				 -I/Users/cc/Documents/course/os/UCORE/ucore_plus/ucore/src/kern-ucore/arch/arm/mach-raspberrypi/linux_fb_drv\
			     -I/Users/cc/Documents/course/os/UCORE/ucore_plus/ucore/src/kern-ucore/arch/arm/mach-raspberrypi/linux_fb_drv/include\
				 -I/Users/cc/Documents/course/os/UCORE/ucore_plus/ucore/src/kern-ucore/arch/arm/mach-raspberrypi/linux_fb_drv/include/generated\
				 -I/Users/cc/Documents/course/os/UCORE/ucore_plus/ucore/src/kern-ucore/arch/arm/mach-raspberrypi/linux_fb_drv/include/uapi\
			     -include linux/kconfig.h 

