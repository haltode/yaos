#ifndef _KERNEL_BITMAP_H
#define _KERNEL_BITMAP_H

#include <stdbool.h>
#include <stdint.h>

typedef struct bitmap_t Bitmap;
struct bitmap_t {
   uint32_t *address;
   uint32_t size;
   uint32_t total_frames;
};

void set_bit(Bitmap *bitmap, uint32_t bit);
void clear_bit(Bitmap *bitmap, uint32_t bit);
bool test_bit(Bitmap *bitmap, uint32_t bit);
uint32_t find_first_free(Bitmap *bitmap);
void set_all_bits(Bitmap *bitmap);

#endif
