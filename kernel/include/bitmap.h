#ifndef _KERNEL_BITMAP_H
#define _KERNEL_BITMAP_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct bitmap bitmap_t;
struct bitmap {
   uint32_t *address;
   uint32_t size;
};

void set_bit(bitmap_t *bitmap, uint32_t bit);
void clear_bit(bitmap_t *bitmap, uint32_t bit);
bool test_bit(bitmap_t *bitmap, uint32_t bit);
uint32_t find_first_n_free(bitmap_t *bitmap, size_t n);
void set_all_bits(bitmap_t *bitmap_t);

#endif
