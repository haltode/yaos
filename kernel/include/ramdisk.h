#ifndef _KERNEL_RAMDISK_H
#define _KERNEL_RAMDISK_H

#include <stddef.h>
#include <stdint.h>

#include <kernel/vfs.h>

Vfs_node *ramdisk_init(void);
void ramdisk_parse_files(void);

uint32_t ramdisk_read(Vfs_node *file, uint32_t offset, size_t size, char *buffer);
Vfs_node *ramdisk_read_dir(Vfs_node *dir, uint32_t index);
Vfs_node *ramdisk_find_dir(Vfs_node *dir, const char *path);

#endif
