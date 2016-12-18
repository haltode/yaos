#include <stdint.h>

#include <kernel/multiboot.h>
#include <kernel/tar.h>

extern Multiboot_info *boot_info;

void ramdisk_init(void)
{
   /* The init ramdisk (which is a tar archive) is loaded as a module by GRUB */
   uint32_t init_entry_addr = *((uint32_t *) boot_info->mods_addr);
   tar_entry_t *init_entry = (tar_entry_t *) init_entry_addr;

   uint32_t nb_files = tar_get_nb_files(init_entry);
}
