#!/bin/sh
set -e
. scripts/build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/vos.kernel isodir/boot/vos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "vos" {
	multiboot /boot/vos.kernel
}
EOF
grub-mkrescue -o vos.iso isodir
