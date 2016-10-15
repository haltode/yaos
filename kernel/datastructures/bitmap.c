#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/bitmap.h>

/*
 * This bitmap datastructure is used to represent physical memory,
 * where each bit corresponds to a frame (4 KiB).
 */

void set_bit(Bitmap *bitmap, uint32_t bit)
{
   bitmap->address[bit / 32] |= (1 << (bit % 32));
}

void clear_bit(Bitmap *bitmap, uint32_t bit)
{
   bitmap->address[bit / 32] &= ~ (1 << (bit % 32));
}

bool test_bit(Bitmap *bitmap, uint32_t bit)
{
   return bitmap->address[bit / 32] & (1 << (bit % 32));
}

uint32_t find_first_n_free(Bitmap *bitmap, size_t n)
{
   if(!n)
      return 0;

   for(uint32_t frame = 0; frame < bitmap->size; ++frame) {
      /* If the frames are not all full */
      if(bitmap->address[frame] != 0xFFFFFFFF) {
         /* Test each bits */

         for(size_t shift = 0; shift < 32; ++shift) {
            uint32_t bit = 1 << shift;
            if(!(bitmap->address[frame] & bit)) {
               /* Test for the given size n */

               uint32_t start = bit + (frame * 32);
               uint32_t free  = 0;
               for(size_t i = 0; i <= n; ++i) {
                  if(!test_bit(bitmap, start + i))
                     ++free;
                  if(free == n)
                     return frame * 32 + shift;
               }
            }
         }
      }
   }

   /* Out of memory */
   return 0;
}

void set_all_bits(Bitmap *bitmap)
{
   memset(bitmap->address, 0xFFFFFFFF, bitmap->size);
}
