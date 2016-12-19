#ifndef _KERNEL_VFS_H
#define _KERNEL_VFS_H

#include <stddef.h>
#include <stdint.h>

enum type_t { FILE_TYPE, DIRECTORY_TYPE };

enum mode_t { CLOSED_MODE, READ_MODE, WRITE_MODE };

typedef struct vfs_node_t vfs_node;
struct vfs_node_t {
   char name[128];
   uint32_t type;
   uint32_t permission;
   uint32_t index;
   uint32_t uid;
   uint32_t gid;
   uint32_t mode;
   size_t size;

   void (*open) (vfs_node *file);
   void (*close) (vfs_node *file);
   uint32_t (*read) (vfs_node *file, uint32_t offset, size_t size, char *buffer);
   uint32_t (*write) (vfs_node *file, uint32_t offset, size_t size, const char *buffer);
   vfs_node *(*read_dir) (vfs_node *file, uint32_t index);
   vfs_node *(*find_dir) (vfs_node *file, const char *path);

   /* Used by mountpoints and symlinks */
   vfs_node *ptr;
};

void vfs_init(void);

void vfs_open(vfs_node *file);
void vfs_close(vfs_node *file);
uint32_t vfs_read(vfs_node *file, uint32_t offset, size_t size, char *buffer);
uint32_t vfs_write(vfs_node *file, uint32_t offset, size_t size, const char *buffer);

#endif
