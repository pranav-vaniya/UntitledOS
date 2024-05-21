#!/bin/bash

set -e

echo -e "\033[0;33m=> Creating Headers\e[0m"

mkdir -p build/UntitledOS/boot/grub
cp configs/grub.cfg build/UntitledOS/boot/grub/grub.cfg
