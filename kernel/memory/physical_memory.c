#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/bitmap.h>
#include <kernel/memory.h>
#include <kernel/multiboot.h>

Bitmap *mem_map = 0;

/* Symbols defined in the linker script */
extern uint32_t kernel_start;
extern uint32_t kernel_end;

/*
 * Setup
 */

static void set_region_free(uint32_t base, size_t size)
{
   uint32_t start_addr = base;
   uint32_t nb_frames = size / FRAME_SIZE;

   for(size_t i = 0; i < nb_frames; ++i) {
      uint32_t frame_addr = start_addr + i * FRAME_SIZE;
      uint32_t bit = frame_addr / FRAME_SIZE;

      clear_bit(mem_map, bit);
   }
}

static void set_region_used(uint32_t base, size_t size)
{
   uint32_t start_addr = base;
   uint32_t nb_frames = size / FRAME_SIZE;

   for(size_t i = 0; i < nb_frames; ++i) {
      uint32_t frame_addr = start_addr + i * FRAME_SIZE;
      uint32_t bit = frame_addr / FRAME_SIZE;

      set_bit(mem_map, bit);
   }
}

void phys_mem_init(Multiboot_info *boot_info)
{
   /* Get the memory info from GRUB */
   uint32_t mem_size_kb = 1024 + boot_info->mem_lower + 
                                 boot_info->mem_upper * 32;
   uint32_t nb_frames   = mem_size_kb / 4;
   uint32_t bitmap_size = nb_frames / 32;

   /* Info about the kernel (4 KiB align the end address) */
   uint32_t kernel_start_addr = (uint32_t) &kernel_start;
   uint32_t kernel_end_addr   = ((uint32_t) &kernel_end & ~(0xFFF)) + 0x1000;
   uint32_t kernel_size       = kernel_end_addr - kernel_start_addr;

   /* Put the bitmap at the end of the kernel */
   uint32_t bitmap_addr = kernel_end_addr;
   /* Only start allocation after the bitmap itfself */
   uint32_t start_addr  = kernel_end_addr + bitmap_size;

   mem_map          = (Bitmap *) bitmap_addr;
   mem_map->address = (uint32_t *) start_addr;
   mem_map->size    = bitmap_size;

   /* By default, the bitmap is marked as full */
   set_all_bits(mem_map);

   /* Free the regions that are available to us */
   Memory_map *mmap = (Memory_map *) boot_info->mmap_addr;
   while((unsigned long) mmap < boot_info->mmap_addr + boot_info->mmap_length) {
      mmap = (Memory_map *) ((unsigned int) mmap + mmap->size + sizeof(mmap->size));

      /* Type 1 means available memory */
      if(mmap->type == 1)
         set_region_free(mmap->base_addr_low, mmap->length_low);
   }

   /* Mark the kernel space as used so we don't overwrite it */
   set_region_used(kernel_start_addr, kernel_size);
   /* Mark the bitmap space (at the end of the kernel) as used too */
   set_region_used(bitmap_addr, bitmap_size);
}

/*
 * Allocation/Deallocation
 */

void *phys_mem_alloc_frames(size_t size)
{
   uint32_t frame = find_first_n_free(mem_map, size);

   /* Out of memory */
   if(!frame)
      return 0;

   for(size_t i = 0; i < size; ++i)
      set_bit(mem_map, frame + i);

   uint32_t address = frame * FRAME_SIZE;
   return (void *) address;
}

void *phys_mem_alloc_frame(void)
{
   return phys_mem_alloc_frames(1);
}

void phys_mem_free_frames(void *frames, size_t size)
{
   uint32_t address = (uint32_t) frames;
   uint32_t frame = address / FRAME_SIZE;

   for(size_t i = 0; i < size; ++i)
      clear_bit(mem_map, frame + i);
}

void phys_mem_free_frame(void *frame)
{
   phys_mem_free_frames(frame, 1);
}
