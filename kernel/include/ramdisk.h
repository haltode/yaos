#ifndef _KERNEL_RAMDISK_H
#define _KERNEL_RAMDISK_H

#include <stddef.h>
#include <stdint.h>

#include <kernel/vfs.h>

vfs_node *ramdisk_init(void);

uint32_t ramdisk_read(vfs_node *file, uint32_t offset, size_t size, char *buffer);
vfs_node *ramdisk_read_dir(vfs_node *file, uint32_t index);
vfs_node *ramdisk_find_dir(vfs_node *file, const char *path);

#endif
