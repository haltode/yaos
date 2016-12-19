#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <kernel/multiboot.h>
#include <kernel/ramdisk.h>
#include <kernel/tar.h>
#include <kernel/vfs.h>

vfs_node *ramdisk;
vfs_node *ramdisk_files;

/*
 * Setup
 */

vfs_node *ramdisk_init(void)
{
   extern Multiboot_info *boot_info;

   /* The init ramdisk (which is a tar archive) is loaded as a module by GRUB */
   uint32_t init_entry_addr = *((uint32_t *) boot_info->mods_addr);
   Tar_entry *init_entry = (Tar_entry *) init_entry_addr;

   uint32_t nb_files = tar_get_nb_files(init_entry);
   ramdisk_files = kcalloc(nb_files, sizeof(vfs_node));
   assert(ramdisk_files != NULL);

   /* Setup the ramdisk */
   strcpy(ramdisk->name, "ramdisk");
   ramdisk->type       = DIRECTORY_TYPE;
   ramdisk->permission = 0;
   ramdisk->index      = -1;
   ramdisk->uid        = 0;
   ramdisk->gid        = 0;
   ramdisk->mode       = CLOSED_MODE;
   ramdisk->size       = 0;
   ramdisk->open       = NULL;
   ramdisk->close      = NULL;
   ramdisk->read       = ramdisk_read;
   ramdisk->write      = NULL;
   ramdisk->read_dir   = ramdisk_read_dir;
   ramdisk->find_dir   = ramdisk_find_dir;
   ramdisk->ptr        = NULL;

   return ramdisk;
}

/*
 * Basic operations
 */

uint32_t ramdisk_read(vfs_node *file, uint32_t offset, size_t size, char *buffer)
{

}

vfs_node *ramdisk_read_dir(vfs_node *file, uint32_t index)
{

}

vfs_node *ramdisk_find_dir(vfs_node *file, const char *path)
{

}
