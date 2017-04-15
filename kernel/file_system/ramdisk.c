#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <kernel/log.h>
#include <kernel/multiboot.h>
#include <kernel/ramdisk.h>
#include <kernel/tar.h>
#include <kernel/vfs.h>

extern Multiboot_info *boot_info;

Vfs_node ramdisk;
Vfs_node *ramdisk_files;
uint32_t nb_ramdisk_files;

Tar_entry *init_entry;


/*
 * Setup
 */

Vfs_node *ramdisk_init(void)
{
   /* The init ramdisk (which is a tar archive) is loaded as a module by GRUB */
   uint32_t init_entry_addr = *((uint32_t *) boot_info->mods_addr);
   init_entry = (Tar_entry *) init_entry_addr;

   /* Setup the ramdisk and all the files */
   nb_ramdisk_files = tar_get_nb_files(init_entry);
   ramdisk_files = calloc(nb_ramdisk_files, sizeof(Vfs_node));
   assert(ramdisk_files != NULL);

   strcpy(ramdisk.name, "/");
   ramdisk.type       = DIRECTORY_TYPE;
   ramdisk.permission = 0;
   ramdisk.index      = 0;
   ramdisk.uid        = 0;
   ramdisk.gid        = 0;
   ramdisk.mode       = CLOSED_MODE;
   ramdisk.size       = 0;
   ramdisk.open       = NULL;
   ramdisk.close      = NULL;
   ramdisk.read       = ramdisk_read;
   ramdisk.write      = NULL;
   ramdisk.read_dir   = ramdisk_read_dir;
   ramdisk.find_dir   = ramdisk_find_dir;

   ramdisk_parse_files();

   return &ramdisk;
}

void ramdisk_parse_files(void)
{
   Tar_entry *current = init_entry;
   size_t i = 0;

   while(true) {
      if(current->name[0] == '\0')
         break;

      strcpy(ramdisk_files[i].name, current->name);
      ramdisk_files[i].permission = 0;
      ramdisk_files[i].index      = i;
      ramdisk_files[i].uid        = 0;
      ramdisk_files[i].gid        = 0;
      ramdisk_files[i].mode       = CLOSED_MODE;
      ramdisk_files[i].size       = strtol(current->size, NULL, 8);
      ramdisk_files[i].open       = NULL;
      ramdisk_files[i].close      = NULL;
      ramdisk_files[i].read       = ramdisk_read;
      ramdisk_files[i].write      = NULL;
      ramdisk_files[i].read_dir   = ramdisk_read_dir;
      ramdisk_files[i].find_dir   = ramdisk_find_dir;

      switch(current->type[0]) {
         case FILE_TAR_TYPE:
            ramdisk_files[i].type = FILE_TYPE;
            break;
         case DIRECTORY_TAR_TYPE:
            ramdisk_files[i].type = DIRECTORY_TYPE;
            break;
         default:
            kernel_log(ERROR_MSG, "Unknown tar file type: '%c'", current->type[0]);
            break;
      }

      ++i;

      current = tar_get_next_entry(current);
      if(!current)
         break;
   }
}

/*
 * Basic operations
 */

uint32_t ramdisk_read(Vfs_node *file, uint32_t offset, size_t size, char *buffer)
{
   Tar_entry *tar_file = tar_get_entry(init_entry, file->index);
   assert(tar_file != NULL);

   char *content = ((char *) tar_file) + TAR_ENTRY_SIZE + offset;
   memcpy(buffer, content, size);
   buffer[size] = '\0';

   return (uint32_t) size;
}

/* Return the child of a directory given the index */
Vfs_node *ramdisk_read_dir(Vfs_node *dir, uint32_t index)
{
   uint32_t dir_depth = vfs_get_depth(dir->name);
   uint32_t n_child = 0;

   for(size_t i = 0; i < nb_ramdisk_files; ++i) {
      uint32_t child_depth = vfs_get_depth(ramdisk_files[i].name);

      /* Check if the file is in the directory */
      if(strstr(ramdisk_files[i].name, dir->name) != NULL) {
         /* A file will have the same depth */
         if(ramdisk_files[i].type == FILE_TYPE && child_depth == dir_depth)
            ++n_child;
         /* A sub-directory's name contains one more '/' so it will
            have +1 depth compare to the directory */
         else if(ramdisk_files[i].type == DIRECTORY_TYPE && child_depth == dir_depth + 1)
            ++n_child;
      }
      
      if(n_child == index)
         return &ramdisk_files[i];
   }

   return NULL;
}

/* Return the child of a directory given the path */
Vfs_node *ramdisk_find_dir(Vfs_node *dir, const char *path)
{
   /* Unused parameter (avoir a warning) */
   (void)(dir);

   for(size_t i = 0; i < nb_ramdisk_files; ++i)
      if(strcmp(path, ramdisk_files[i].name) == 0)
         return &ramdisk_files[i];

   return NULL;
}
