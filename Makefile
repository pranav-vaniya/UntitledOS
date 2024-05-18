.PHONY: all build run clean

all: clean headers build run

headers:
	mkdir -p build/UntitledOS/boot/grub
	cp configs/grub.cfg build/UntitledOS/boot/grub/grub.cfg

build:
	gcc -m32 -fno-stack-protector -fno-builtin -c kernel/kernel.c -o build/kernel.o
	gcc -m32 -fno-stack-protector -fno-builtin -c kernel/vga.c -o build/vga.o
	nasm -f elf32 boot/boot.s -o build/boot.o
	ld -m elf_i386 -T linker.ld -o build/UntitledOS/boot/kernel build/boot.o build/kernel.o build/vga.o
	grub-mkrescue -o UntitledOS.iso build/UntitledOS

run:
	qemu-system-x86_64 -cdrom UntitledOS.iso

clean:
	rm -rf build/
	rm -f UntitledOS.iso
