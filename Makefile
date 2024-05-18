.PHONY: all build run clean

CFLAGS = -m32 -fno-stack-protector -fno-builtin

all: clean headers build run

headers:
	mkdir -p build/UntitledOS/boot/grub
	cp configs/grub.cfg build/UntitledOS/boot/grub/grub.cfg

build:
	gcc $(CFLAGS) -c kernel/kernel.c -o build/kernel.o
	gcc $(CFLAGS) -c kernel/vga.c -o build/vga.o
	gcc $(CFLAGS) -c kernel/gdt.c -o build/gdt.o
	gcc $(CFLAGS) -c kernel/util.c -o build/util.o
	gcc $(CFLAGS) -c kernel/idt.c -o build/idt.o

	nasm -f elf32 i386/boot.s -o build/boot.o
	nasm -f elf32 i386/gdt.s -o build/gdts.o
	nasm -f elf32 i386/idt.s -o build/idts.o
	
	ld -m elf_i386 -T linker.ld -o build/UntitledOS/boot/kernel build/boot.o build/kernel.o build/vga.o build/gdt.o build/gdts.o build/util.o build/idt.o build/idts.o
	grub-mkrescue -o UntitledOS.iso build/UntitledOS

run:
	qemu-system-x86_64 -cdrom UntitledOS.iso

clean:
	rm -rf build/
	rm -f UntitledOS.iso
