#!/bin/bash

set -e

CC="i686-elf-gcc"
CFLAGS="-m32 -fno-stack-protector -fno-builtin"
LD="i686-elf-ld"
ASM="nasm"
ASMFLAGS="-f elf32"

echo -e "\033[0;33m=> Compiling C Source Files\e[0m"

# Take all the .c source files from kernel directory
# Extract the base_name e.g. foo from foo.c
# Compile that file to generate foo.o and put it into build directory
for file in kernel/*.c; do
    base_name=$(basename "$file" .c)
    $CC $CFLAGS -c "$file" -o "build/$base_name.o"
    echo "    CC     $file"
done

echo -e "\033[0;33m=> Assembling Source Files\e[0m"

# Take all the .s source files from i386 directory
# Extract the base_name e.g. foo from foo.s
# Compile that file to generate foo-asm.o and put it into build directory
for file in i386/*.s; do
    base_name=$(basename "$file" .s)
    $ASM $ASMFLAGS "$file" -o "build/$base_name-asm.o"
    echo "    ASM    $file"
done

echo -e "\033[0;33m=> Linking Object Files\e[0m"

# Link all the .o files in the build directory
$LD -T linker.ld -o build/UntitledOS/boot/kernel build/*.o
