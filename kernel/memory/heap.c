#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/memory.h>

uint32_t *kernel_heap_top;

/*
 * Setup
 */

void heap_init(void)
{
   kernel_heap_top = (uint32_t *) KERNEL_HEAP_ADDR;
}

/*
 * 
 */

void *heap_expand(ptrdiff_t increment)
{
   /* TODO: check heap overflow */

   /* Expand the heap */
   if(increment >= 0) {
      uint32_t nb_pages = increment / FRAME_SIZE;   
      void *address = kernel_heap_top;

      for(size_t i = 0; i < nb_pages; ++i) {
         void *frame = phys_mem_alloc_frame();
         /* TODO: check allocation */

         virt_mem_map_page(frame, kernel_heap_top);

         memset(kernel_heap_top, 0, FRAME_SIZE);
         kernel_heap_top += FRAME_SIZE;
      }

      return address;
   }
   /* Contract the heap */
   else {
      uint32_t nb_pages = (-increment) / FRAME_SIZE;

      for(size_t i = 0; i < nb_pages; ++i) {
         kernel_heap_top -= FRAME_SIZE;

         void *frame = virt_mem_get_phys_addr(kernel_heap_top);

         phys_mem_free_frame(frame);
         virt_mem_unmap_page(kernel_heap_top);
      }

      return kernel_heap_top;
   }
}
