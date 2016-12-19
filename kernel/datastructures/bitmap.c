#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/bitmap.h>
#include <kernel/memory.h>

/*
 * This bitmap datastructure is used to represent physical memory,
 * where each bit corresponds to a frame (4 KiB).
 */

void set_bit(Bitmap *bitmap, uint32_t bit)
{
   assert((bit / 32) < bitmap->size);
   bitmap->address[bit / 32] |= (1 << (bit % 32));
}

void clear_bit(Bitmap *bitmap, uint32_t bit)
{
   assert((bit / 32) < bitmap->size);
   bitmap->address[bit / 32] &= ~ (1 << (bit % 32));
}

bool test_bit(Bitmap *bitmap, uint32_t bit)
{
   assert((bit / 32) < bitmap->size);
   return bitmap->address[bit / 32] & (1 << (bit % 32));
}

uint32_t find_first_free(Bitmap *bitmap)
{
   for(uint32_t frame = 0; frame < bitmap->size; ++frame) {
      /* If the frames are not all full */
      if(bitmap->address[frame] != 0xFFFFFFFF) {
         /* Test each bits */
         for(size_t shift = 0; shift < 32; ++shift) {
            uint32_t bit = 1 << shift;
            if(!(bitmap->address[frame] & bit))
               return frame * 32 + shift;
         }
      }
   }

   /* Out of memory */
   return 0;
}

void set_all_bits(Bitmap *bitmap)
{
   for(uint32_t frame = 0; frame < bitmap->total_frames; ++frame)
      set_bit(bitmap, frame);
}
