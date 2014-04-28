obj-y := bcm2708.dummy.o bcm2708_fb.o

TARGET_CFLAGS += -D__KERNEL__ \
				 -D__KERN__ \
				 -DKBUILD_BASENAME=\"dde\" \
			     -DKBUILD_MODNAME=\"dde\" \
			     -D__LINUX_ARM_ARCH__ \
			     -include linux/kconfig.h \
			     -I./bcm2708.d \
				 -I./bcm2708.d/generated \
			     -I./bcm2708.d/uapi 

