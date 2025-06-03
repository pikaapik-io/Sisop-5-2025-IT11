SRC = src
INC = include
BUILD = build

CFLAGS = -m32 -ffreestanding -c
LDFLAGS = -m elf_i386 -Ttext 0x1000 --oformat binary

prepare:
	mkdir -p $(BUILD)
	dd if=/dev/zero of=$(BUILD)/floppy.img bs=512 count=2880

bootloader:
	nasm -f bin $(SRC)/bootloader.asm -o $(BUILD)/bootloader.bin

stdlib:
	gcc $(CFLAGS) $(SRC)/std_lib.c -o $(BUILD)/std_lib.o

shell:
	gcc $(CFLAGS) $(SRC)/shell.c -o $(BUILD)/shell.o

kernel:
	gcc $(CFLAGS) $(SRC)/kernel.c -o $(BUILD)/kernel.o
	nasm -f elf $(SRC)/kernel.asm -o $(BUILD)/kernel_asm.o

link:
	ld $(LDFLAGS) -o $(BUILD)/kernel.bin $(BUILD)/kernel.o $(BUILD)/kernel_asm.o $(BUILD)/shell.o $(BUILD)/std_lib.o
	cat $(BUILD)/bootloader.bin $(BUILD)/kernel.bin > $(BUILD)/floppy.img

build: prepare bootloader stdlib shell kernel link
	@echo "✅ Build complete! Run with Bochs or QEMU."
