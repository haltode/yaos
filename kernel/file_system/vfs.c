#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/log.h>
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

static Vfs_node *vfs_search_file(Vfs_node *parent, const char *path)
{
   assert(parent != NULL);
   
   Vfs_node *child;
   size_t index_child = 1;
   while((child = vfs_read_dir(parent, index_child)) != NULL) {
      if(strcmp(child->name, path) == 0)
         return child;

      if(child->type == DIRECTORY_TYPE) {
         Vfs_node *recursive_child = vfs_search_file(child, path);
         if(recursive_child != NULL)
            return recursive_child;
      }

      ++index_child;
   }

   return NULL;
}

Vfs_node *vfs_open(const char *path, const char *mode)
{
   Vfs_node *file = vfs_search_file(root, path);
   assert(file != NULL);
   assert(file->type == FILE_TYPE);

   if(strcmp(mode, "r") == 0)
      file->mode = READ_MODE;
   else if(strcmp(mode, "w") == 0)
      file->mode = WRITE_MODE;
   else
      kernel_log(ERROR_MSG, "Unknown file mode: '%s'", mode);
   
   return file;
}

void vfs_close(Vfs_node *file)
{
   assert(file != NULL);
   assert(file->mode != CLOSED_MODE);

   if(file->close != 0)
      file->close(file);
}

uint32_t vfs_read(Vfs_node *file, uint32_t offset, size_t size, char *buffer)
{
   assert(file != NULL);
   assert(file->mode == READ_MODE);

   if(file->read != 0)
      return file->read(file, offset, size, buffer);
   else
      return 0;
}

uint32_t vfs_write(Vfs_node *file, uint32_t offset, size_t size, const char *buffer)
{
   assert(file != NULL);
   assert(file->mode == WRITE_MODE);

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
