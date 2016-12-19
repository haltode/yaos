#ifndef _KERNEL_TAR_H
#define _KERNEL_TAR_H

#include <stdbool.h>
#include <stdint.h>

#define TAR_ENTRY_SIZE 512

typedef struct tar_entry_t Tar_entry;
struct tar_entry_t {
   char name[100];
   char mode[8];
   char uid[8];
   char gid[8];
   char size[12];
   char modif_time[12];
   char checksum[8];
   char type[1];
};

bool is_tar_entry_valid(Tar_entry *entry);
Tar_entry *tar_get_entry(Tar_entry *init_entry, uint32_t index);
Tar_entry *tar_get_next_entry(Tar_entry *entry);
uint32_t tar_get_nb_files(Tar_entry *init_entry);

#endif
