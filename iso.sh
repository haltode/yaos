#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/yaos.kernel isodir/boot/yaos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "yaos" {
	multiboot /boot/yaos.kernel
}
EOF
grub-mkrescue -o yaos.iso isodir
