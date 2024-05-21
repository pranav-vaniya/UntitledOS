#!/bin/bash

set -e

echo -e "\033[0;33m=> Launching QEMU\e[0m"

qemu-system-x86_64 -cdrom UntitledOS.iso
