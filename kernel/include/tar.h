#ifndef _KERNEL_TAR_H
#define _KERNEL_TAR_H

#include <stdbool.h>
#include <stdint.h>

#define TAR_ENTRY_SIZE 512

typedef struct tar_entry_t tar_entry_t;
struct tar_entry_t
{
   char filename[100];
   char mode[8];
   char uid[8];
   char gid[8];
   char size[12];
   char mtime[12];
   char checksum[8];
   char typeflag[1];
};

bool is_tar_entry_valid(tar_entry_t *entry);
tar_entry_t *tar_get_next_entry(tar_entry_t *entry);
uint32_t tar_get_nb_files(tar_entry_t *init_entry);

#endif
