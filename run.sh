#!/bin/sh

# Exit immediately in case a command generates error
set -e

# Clean up
echo "├─── Cleaning Up ───\n"
./clean.sh

# Create Headers
echo -e "\n├─── Creating Headers ───\n"
./headers.sh

# Build the iso
echo -e "\n├─── Compiling Kernel ───\n"
./build.sh

# Start qemu
echo -e "\n├─── Starting QEMU ───\n"
./qemu.sh

# Clean up again
echo -e "\n├─── Cleaning Up ───\n"
./clean.sh