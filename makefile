prepare:
	@echo "Preparing build environment..."
	mkdir -p build

bootloader:
	@echo "Building bootloader..."
	nasm -f bin bootloader.asm -o build/bootloader.bin

stdlib:
	@echo "Compiling standard library..."
	gcc -c stdlib.c -o build/stdlib.o

shell:
	@echo "Compiling shell..."
	gcc -c shell.c -o build/shell.o

kernel:
	@echo "Compiling kernel..."
	gcc -c kernel.c -o build/kernel.o

link:
	@echo "Linking all components..."
	ld -o build/os.bin build/bootloader.bin build/stdlib.o build/shell.o build/kernel.o

build: prepare bootloader stdlib shell kernel link
	@echo "Build complete!"