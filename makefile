# Makefile

CC = gcc
CFLAGS = -Wall -g

prepare:
    dd if=/dev/zero of=floppy.img bs=512 count=2880

bootloader:
    nasm -f bin bootloader.asm -o bin/bootloader.bin

stdlib:
    gcc -c src/std_lib.c -o bin/std_lib.o

shell:
    gcc -c src/shell.c -o bin/shell.o

kernel:
    nasm -f elf src/kernel.asm -o bin/kernel_asm.o
    gcc -c src/kernel.c -o bin/kernel.o

link:
    ld -m elf_i386 -o bin/floppy.img bin/bootloader.bin bin/kernel_asm.o bin/kernel.o bin/std_lib.o bin/shell.o

build: prepare bootloader stdlib kernel shell link
