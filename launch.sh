#!/usr/bin/bash

echo -e "Step 1/5: Updating package lists and installing build/runtime dependencies...\n"
apt-get update && apt-get install -y gcc make perl qemu-system-x86 gcc-multilib

echo -e "Step 2/5: Switching to the xv6 project directory...\n"
cd /xv6

echo -e "Step 3/5: Cleaning any previous build output...\n"
make clean

echo -e "Step 4/5: Building the kernel and user programs...\n"
make

echo -e "Step 5/5: Starting xv6 in QEMU (no GUI)...\n"
make qemu-nox
