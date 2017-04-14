#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <kernel/log.h>
#include <kernel/ramdisk.h>
#include <kernel/tar.h>
#include <kernel/vfs.h>

void test_ramdisk(void)
{
   extern Vfs_node *root;
   extern Vfs_node *ramdisk_files;
   extern uint32_t nb_ramdisk_files;
   extern Tar_entry *init_entry;

   printf("nb_ramdisk_files: %d\n", nb_ramdisk_files);
   for(size_t i = 0; i < nb_ramdisk_files; ++i) {
      printf("Found '%s': ", ramdisk_files[i].name);
      if(ramdisk_files[i].type == DIRECTORY_TYPE)
         printf("(directory)");
      else if(ramdisk_files[i].type == FILE_TYPE) {
         printf("(file, %d bytes)", ramdisk_files[i].size);

         Tar_entry *file = tar_get_entry(init_entry, i);
         char buf[ramdisk_files[i].size + 1];
         char *content = ((char *) file) + TAR_ENTRY_SIZE;

         memcpy(buf, content, ramdisk_files[i].size);
         buf[ramdisk_files[i].size] = '\0';
         printf("\nContent: %s", buf);
      }
      else
         kernel_log(ERROR_MSG, "Unknown file type: '%d'", ramdisk_files[i].type);

      printf("\n");
   }

   Vfs_node *test_open = vfs_open("user/test_file", "r");
   printf("test open: %s\n", test_open->name);

   Vfs_node *test_read_dir = vfs_read_dir(root, 1);
   printf("test read dir: %s\n", test_read_dir->name);

   Vfs_node *test_find_dir = vfs_find_dir(root, "user/test_dir/test_subfile");
   printf("test find dir: %s\n", test_find_dir->name);
}
