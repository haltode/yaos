#!/bin/sh
mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/yaos.kernel isodir/boot/yaos.kernel
cp config/initrd.tar isodir/boot/initrd.tar
cp config/grub.cfg isodir/boot/grub/grub.cfg

grub-mkrescue -o yaos.iso isodir
