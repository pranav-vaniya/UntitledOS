#!/bin/bash

set -e

echo -e "\033[0;33m=> Generating ISO Image\e[0m"

grub-mkrescue -o UntitledOS.iso build/UntitledOS
