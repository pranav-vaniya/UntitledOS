#!/bin/sh

# Exit immediately in case a command generates error
set -e

# Clean up
echo -e "├─── Cleaning Up ───\n"
scripts/clean.sh

# Create Headers
echo -e "\n├─── Creating Headers ───\n"
scripts/headers.sh

# Build the iso
echo -e "\n├─── Compiling Kernel ───\n"
scripts/build.sh

# Start qemu
echo -e "\n├─── Starting QEMU ───\n"
scripts/qemu.sh

# Clean up again
echo -e "\n├─── Cleaning Up ───\n"
scripts/clean.sh