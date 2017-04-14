#ifndef _KERNEL_VFS_H
#define _KERNEL_VFS_H

#include <stddef.h>
#include <stdint.h>

enum type_t { FILE_TYPE, DIRECTORY_TYPE };

enum mode_t { CLOSED_MODE, READ_MODE, WRITE_MODE };

typedef struct vfs_node_t Vfs_node;
struct vfs_node_t {
   char name[128];
   uint32_t type;
   uint32_t permission;
   uint32_t index;
   uint32_t uid;
   uint32_t gid;
   uint32_t mode;
   size_t size;

   void (*open) (Vfs_node *file);
   void (*close) (Vfs_node *file);
   uint32_t (*read) (Vfs_node *file, uint32_t offset, size_t size, char *buffer);
   uint32_t (*write) (Vfs_node *file, uint32_t offset, size_t size, const char *buffer);
   Vfs_node *(*read_dir) (Vfs_node *dir, uint32_t index);
   Vfs_node *(*find_dir) (Vfs_node *dir, const char *path);

   /* Used by mountpoints and symlinks */
   Vfs_node *ptr;
};

void vfs_init(void);

Vfs_node *vfs_open(const char *path, const char *mode);
void vfs_close(Vfs_node *file);
uint32_t vfs_read(Vfs_node *file, uint32_t offset, size_t size, char *buffer);
uint32_t vfs_write(Vfs_node *file, uint32_t offset, size_t size, const char *buffer);
Vfs_node *vfs_read_dir(Vfs_node *dir, uint32_t index);
Vfs_node *vfs_find_dir(Vfs_node *dir, const char *path);

uint32_t vfs_get_depth(const char *path);

#endif
