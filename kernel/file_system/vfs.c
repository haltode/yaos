#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include <kernel/ramdisk.h>
#include <kernel/vfs.h>

vfs_node *root;

/*
 * Setup
 */

void vfs_init(void)
{
   root = ramdisk_init();
}

/*
 * Basic operations
 */

void vfs_open(vfs_node *file)
{
   /* TODO: more checks */
   assert(file != NULL);

   if(file->open != 0)
      file->open(file);
}

void vfs_close(vfs_node *file)
{
   assert(file != NULL);

   if(file->close != 0)
      file->close(file);
}

uint32_t vfs_read(vfs_node *file, uint32_t offset, size_t size, char *buffer)
{
   assert(file != NULL);

   if(file->read != 0)
      return file->read(file, offset, size, buffer);
   else
      return 0;
}

uint32_t vfs_write(vfs_node *file, uint32_t offset, size_t size, const char *buffer)
{
   assert(file != NULL);

   if(file->write != 0)
      return file->write(file, offset, size, buffer);
   else
      return 0;
}

/* TODO: Implement read_dir and find_dir */
