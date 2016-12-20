#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include <kernel/tar.h>

/* TODO: Add more info about the tar extension */

bool is_tar_entry_valid(Tar_entry *entry)
{
   assert(entry != NULL);

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

Tar_entry *tar_get_entry(Tar_entry *init_entry, uint32_t index)
{
   assert(init_entry != NULL);

   Tar_entry *current = init_entry;
   size_t i = 0;

   while(true) {
      if(current->name[0] == '\0')
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

Tar_entry *tar_get_next_entry(Tar_entry *entry)
{
   assert(entry != NULL);

   uint32_t address = (uint32_t) entry;
   uint32_t file_size = strtol(entry->size, NULL, 8);
  
   address += ((file_size / 512) + 1) * 512;
   if(file_size % 512 != 0)
      address += 512;

   Tar_entry *next_entry = (Tar_entry *) address;

   if(is_tar_entry_valid(next_entry))
      return next_entry;
   else
      return NULL;
}

uint32_t tar_get_nb_files(Tar_entry *init_entry)
{
   assert(init_entry != NULL);

   Tar_entry *current = init_entry;
   uint32_t nb_files = 0;

   while(true) {
      if(current->name[0] == '\0')
         break;

      current = tar_get_next_entry(current);
      ++nb_files;
      
      if(!current)
         break;
   }
   
   return nb_files;
}
