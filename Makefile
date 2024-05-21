.PHONY: all build run clean

CC = i686-elf-gcc
CFLAGS = -m32 -fno-stack-protector -fno-builtin
LD = i686-elf-ld

all: clean headers build run

headers:
	mkdir -p build/UntitledOS/boot/grub
	cp configs/grub.cfg build/UntitledOS/boot/grub/grub.cfg

build:
	$(CC) $(CFLAGS) -c kernel/kernel.c -o build/kernel.o
	$(CC) $(CFLAGS) -c kernel/vga.c -o build/vga.o
	$(CC) $(CFLAGS) -c kernel/gdt.c -o build/gdt.o
	$(CC) $(CFLAGS) -c kernel/util.c -o build/util.o
	$(CC) $(CFLAGS) -c kernel/idt.c -o build/idt.o
	$(CC) $(CFLAGS) -c kernel/timer.c -o build/timer.o
	$(CC) $(CFLAGS) -c kernel/keyboard.c -o build/keyboard.o
	$(CC) $(CFLAGS) -c kernel/stdio.c -o build/stdio.o
	$(CC) $(CFLAGS) -c kernel/memory.c -o build/memory.o
	$(CC) $(CFLAGS) -c kernel/kmalloc.c -o build/kmalloc.o
	$(CC) $(CFLAGS) -c kernel/shell.c -o build/shell.o
	$(CC) $(CFLAGS) -c kernel/string.c -o build/string.o

	nasm -f elf32 i386/boot.s -o build/boot.o
	nasm -f elf32 i386/gdt.s -o build/gdts.o
	nasm -f elf32 i386/idt.s -o build/idts.o
	
	$(LD) -T linker.ld -o build/UntitledOS/boot/kernel build/boot.o build/kernel.o build/vga.o build/gdt.o build/gdts.o build/util.o build/idt.o build/idts.o build/timer.o build/keyboard.o build/stdio.o build/memory.o build/kmalloc.o build/shell.o build/string.o
	grub-mkrescue -o UntitledOS.iso build/UntitledOS

run:
	qemu-system-x86_64 -cdrom UntitledOS.iso

clean:
	rm -rf build/
	rm -f UntitledOS.iso
