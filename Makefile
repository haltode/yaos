export HOST=i686-elf
export HOST_ARCH=i386

export DEST_DIR=$(shell pwd)/sysroot

export AR=$(HOST)-ar
export AS=$(HOST)-as
export CC=$(HOST)-gcc --sysroot=$(DEST_DIR) -isystem=$(INCLUDE_DIR)

export PREFIX=/usr
export EXEC_PREFIX=$(PREFIX)
export BOOT_DIR=/boot
export LIB_DIR=$(EXEC_PREFIX)/lib
export INCLUDE_DIR=$(PREFIX)/include

export CFLAGS=-O2 -g
export CPPFLAGS=


LIBC_DIR=libc
KERNEL_DIR=kernel


all: yaos

yaos:
	mkdir -p sysroot
	make -C $(LIBC_DIR) install-headers
	make -C $(KERNEL_DIR) install-headers
	make -C $(LIBC_DIR) install
	make -C $(KERNEL_DIR) install
	./scripts/setup_iso.sh

clean:
	make -C $(LIBC_DIR) clean
	make -C $(KERNEL_DIR) clean
	rm -rfv sysroot
	rm -rfv isodir
	rm -rfv yaos.iso

qemu:
	qemu-system-x86_64 -cdrom yaos.iso
