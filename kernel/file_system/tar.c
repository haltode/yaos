#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <kernel/tar.h>

bool is_tar_entry_valid(tar_entry_t *entry)
{
   uint8_t *address = (uint8_t *) entry;
   uint32_t checksum = strtol(entry->checksum, NULL, 8);

   for(size_t i = 0; i < TAR_ENTRY_SIZE; ++i) {
      if(i >= 148 && i < 156)
         checksum -= 32;
      else
         checksum -= address[i];
   }

   return !checksum;
}

tar_entry_t *tar_get_entry(tar_entry_t *init_entry, uint32_t index)
{
   tar_entry_t *current = init_entry;
   size_t i = 0;

   while(true) {
      if(current->filename[0] == '\0')
         break;

      if(index == i)
         return current;

      current = tar_get_next_entry(current);
      ++i;

      if(!current)
         break;
   }

   return NULL;
}

tar_entry_t *tar_get_next_entry(tar_entry_t *entry)
{
   uint32_t address = (uint32_t) entry;
   uint32_t file_size = strtol(entry->size, NULL, 8);
  
   address += ((file_size / 512) + 1) * 512;
   if(file_size % 512 != 0)
      address += 512;

   tar_entry_t *next_entry = (tar_entry_t *) address;

   if(is_tar_entry_valid(next_entry))
      return next_entry;
   else
      return NULL;
}

uint32_t tar_get_nb_files(tar_entry_t *init_entry)
{
   tar_entry_t *current = init_entry;
   uint32_t nb_files = 0;

   while(true) {
      if(current->filename[0] == '\0')
         break;

      current = tar_get_next_entry(current);
      ++nb_files;
      
      if(!current)
         break;
   }
   
   return nb_files;
}
