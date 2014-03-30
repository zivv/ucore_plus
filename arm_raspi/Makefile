BOARD_NAME:= rpi
TARGET:=elfloader-$(BOARD_NAME).bin
CROSS_COMPILE:=arm-none-eabi-
LD:=$(CROSS_COMPILE)ld
CC:=$(CROSS_COMPILE)gcc
OBJCOPY:=$(CROSS_COMPILE)objcopy

BOOTLOADER_BASE:=0x8000
CFLAGS:= -Wall -nostdinc -nostdlib -fno-builtin -DBOOTLOADER_BASE=$(BOOTLOADER_BASE) -march=armv6

OBJS := bootasm.o bootmain.o eabi_utils.o memcpy.o

#all: $(TARGET) boot.scr kernel.img
all: kernel.img

#KERNEL_ELF :=/Users/cc/Documents/course/OS/UCORE/ucore_plus/ucore/obj/kernel/kernel-arm.elf 
KERNEL_ELF := /Users/cc/Documents/course/OS/UCORE/ucore_plus/ucore/obj/kernel/kernel-arm.elf
kernel.img: $(TARGET) $(KERNEL_ELF)
	rm -f $@
	dd if=$(TARGET) of=$@
	dd if=$(KERNEL_ELF) of=$@ seek=8 conv=notrunc # $(TARGET) occupies 4K

$(TARGET).elf: $(OBJS) bootloader.ld
	$(LD) -T bootloader.ld -o $@ $(OBJS)

$(TARGET): $(TARGET).elf
	$(OBJCOPY) -S -O binary $< $@

%.o: %.S
	$(CC) -c $(CFLAGS) -o $@ $<

bootloader.ld : bootloader.ld.in
	sed 's/TEXT_BASE/$(BOOTLOADER_BASE)/' $< > $@	

%.scr: %.cmd
	mkimage -A arm -O linux -T script -C none -a 0 -e 0 -n "bootscr" -d $< $@

clean:
	rm -f bootloader.ld *.scr kernel.img
	rm -f *.o $(TARGET) $(TARGET).elf
	rm -f ccjmp.bin
