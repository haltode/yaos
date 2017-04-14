#############
# Locations #
#############

CURDIR = $(shell pwd)

# Main destination directories
SYSROOT         = $(CURDIR)/sysroot
SYSROOT_BOOT    = $(SYSROOT)/boot
SYSROOT_USR     = $(SYSROOT)/usr
SYSROOT_USR_LIB = $(SYSROOT_USR)/lib
SYSROOT_USR_INC = $(SYSROOT_USR)/include

# Main kernel directories
KERNEL        = kernel
KERNEL_INC    = $(KERNEL)/include
KERNEL_LINKER = $(KERNEL)/linker.ld
KERNEL_BIN    = $(KERNEL)/yaos.kernel

# Main libc directories
# Libc: Hosted version (user-space programming)
# Libk: Freestanding version (kernel programming)
LIBC     = libc
LIBC_INC = $(LIBC)/include
LIBC_BIN = $(LIBC)/libc.a
LIBK_BIN = $(LIBC)/libk.a

#############
# Toolchain #
#############

# Virtual machine
VM             = qemu-system-x86_64
VM_FLAGS       = -cdrom
VM_DEBUG_FLAGS = -s -S

# Cross-compiler
HOST = i686-elf
AR   = $(HOST)-ar
AS   = $(HOST)-as
CC   = $(HOST)-gcc --sysroot=$(SYSROOT) -isystem=/usr/include

CFLAGS   = -O2 -g -ffreestanding -Wall -Wextra
CPPFLAGS =

# Kernel build flags
KERNEL_CFLAGS   = $(CFLAGS)
KERNEL_CPPFLAGS = $(CPPFLAGS) -D__is_kernel -Iinclude
KERNEL_LIBS     = -nostdlib -lk -lgcc

# Libc/libk build flags
LIBC_CFLAGS   = $(CFLAGS)
LIBC_CPPFLAGS = $(CPPFLAGS) -D__is_libc -Iinclude
LIBK_CFLAGS   = $(LIBC_CFLAGS)
LIBK_CPPFLAGS = $(LIBC_CPPFLAGS) -D__is_libk

# Kernel objects
KERNEL_SRC  = $(shell find $(KERNEL) -name '*.c' -o -name '*.S')
KERNEL_CRT  = $(KERNEL)/crti.o $(KERNEL)/crtn.o
KERNEL_OBJS = $(filter-out $(KERNEL_CRT), $(addsuffix .o, $(basename $(KERNEL_SRC))))

KERNEL_COMPLETE_OBJS = $(KERNEL)/crti.o $(KERNEL)/crtbegin.o \
                       $(KERNEL_OBJS) \
                       $(KERNEL)/crtend.o $(KERNEL)/crtn.o
KERNEL_LINK_LIST     = $(KERNEL)/crti.o $(KERNEL)/crtbegin.o \
                       $(KERNEL_OBJS) $(KERNEL_LIBS) \
                       $(KERNEL)/crtend.o $(KERNEL)/crtn.o

# Libc/libk objects
LIBC_SRC  = $(shell find $(LIBC) -name '*.c')
LIBC_OBJS = $(addsuffix .o, $(basename $(LIBC_SRC)))
LIBK_OBJS = $(LIBC_OBJS:.o=.libk.o)

############
# Commands #
############

.PHONY: all prepare_sysroot
.PHONY: clean_kernel clean_libc clean_libk clean
.PHONY: run

all: yaos

yaos: prepare_sysroot $(LIBK_BIN) $(KERNEL_BIN)
	scripts/setup_initrd.sh
	scripts/setup_iso.sh

prepare_sysroot:
	mkdir -p $(SYSROOT)
	mkdir -p $(SYSROOT_USR_INC)
	mkdir -p $(SYSROOT_USR_INC)/kernel
	cp -R --preserve=timestamps $(LIBC_INC)/. $(SYSROOT_USR_INC)/.
	cp -R --preserve=timestamps $(KERNEL_INC)/. $(SYSROOT_USR_INC)/kernel/.
	mkdir -p $(SYSROOT_USR_LIB)
	mkdir -p $(SYSROOT_BOOT)

##########
# Kernel #
##########

$(KERNEL_BIN): $(KERNEL_COMPLETE_OBJS)
	$(CC) -T $(KERNEL_LINKER) -o $@ $(KERNEL_CFLAGS) $(KERNEL_LINK_LIST)
	grub-file --is-x86-multiboot $(KERNEL_BIN)
	cp $(KERNEL_BIN) $(SYSROOT_BOOT)

$(KERNEL)/crtbegin.o $(KERNEL)/crtend.o:
	OBJ=`$(CC) $(KERNEL_CFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

$(KERNEL)/%.o: $(KERNEL)/%.c
	$(CC) -MD -c $< -o $@ -std=gnu11 $(KERNEL_CFLAGS) $(KERNEL_CPPFLAGS)

$(KERNEL)/%.o: $(KERNEL)/%.S
	$(CC) -MD -c $< -o $@ $(KERNEL_CFLAGS) $(KERNEL_CPPFLAGS)

########
# Libc #
########

$(LIBC_BIN): $(LIBC_OBJS)
	$(AR) rcs $@ $(LIBC_OBJS)
	cp $(LIBC_BIN) $(SYSROOT_USR_LIB)

$(LIBC)/%.o: $(LIBC)/%.c
	$(CC) -MD -c $< -o $@ -std=gnu11 $(LIBC_CFLAGS) $(LIBC_CPPFLAGS)

########
# Libk #
########

$(LIBK_BIN): $(LIBK_OBJS)
	$(AR) rcs $@ $(LIBK_OBJS)
	cp $(LIBK_BIN) $(SYSROOT_USR_LIB)

$(LIBC)/%.libk.o: $(LIBC)/%.c
	$(CC) -MD -c $< -o $@ -std=gnu11 $(LIBK_CFLAGS) $(LIBK_CPPFLAGS)

###################
# Virtual machine #
###################

run:
	$(VM) $(VM_FLAGS) yaos.iso

debug:
	$(VM) $(VM_DEBUG_FLAGS) $(VM_FLAGS) yaos.iso

############
# Cleaning #
############

clean_kernel:
	rm -f $(KERNEL_BIN)
	rm -f $(KERNEL_COMPLETE_OBJS)
	rm -f $(KERNEL_COMPLETE_OBJS:.o=.d)

clean_libc:
	rm -f $(LIBC_BIN)
	rm -f $(LIBC_OBJS)
	rm -f $(LIBC_OBJS:.o=.d)

clean_libk:
	rm -f $(LIBK_BIN)
	rm -f $(LIBK_OBJS)
	rm -f $(LIBK_OBJS:.libk.o=.libk.d)

clean: clean_kernel clean_libc clean_libk
	rm -rfv $(SYSROOT)
	rm -rfv isodir
	rm -rfv yaos.iso
