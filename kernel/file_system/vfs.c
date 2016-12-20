#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include <kernel/ramdisk.h>
#include <kernel/vfs.h>

Vfs_node *root;

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

void vfs_open(Vfs_node *file)
{
   assert(file != NULL);

   if(file->open != 0)
      file->open(file);
}

void vfs_close(Vfs_node *file)
{
   assert(file != NULL);

   if(file->close != 0)
      file->close(file);
}

uint32_t vfs_read(Vfs_node *file, uint32_t offset, size_t size, char *buffer)
{
   assert(file != NULL);

   if(file->read != 0)
      return file->read(file, offset, size, buffer);
   else
      return 0;
}

uint32_t vfs_write(Vfs_node *file, uint32_t offset, size_t size, const char *buffer)
{
   assert(file != NULL);

   if(file->write != 0)
      return file->write(file, offset, size, buffer);
   else
      return 0;
}

Vfs_node *vfs_read_dir(Vfs_node *dir, uint32_t index)
{
   assert(dir != NULL);
   assert(dir->type == DIRECTORY_TYPE);

   if(dir->read_dir != 0)
      return dir->read_dir(dir, index);
   else
      return NULL;
}

Vfs_node *vfs_find_dir(Vfs_node *dir, const char *path)
{
   assert(dir != NULL);
   assert(dir->type == DIRECTORY_TYPE);

   if(dir->find_dir != 0)
      return dir->find_dir(dir, path);
   else
      return NULL;

}

/*
 * Miscellaneous
 */

/* Count number of '/' in the file's name to deduct the depth */
uint32_t vfs_get_depth(const char *path)
{
   uint32_t depth = 0;

   for(size_t i = 0; path[i] != '\0'; ++i)
      if(path[i] == '/')
         ++depth;

   return depth;
}
