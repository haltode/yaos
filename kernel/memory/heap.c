#include <stdint.h>

#include <kernel/memory.h>

uint32_t *kernel_heap_top;

/*
 * Setup
 */

void heap_init(void)
{
   kernel_heap_top = (uint32_t *) KERNEL_HEAP_ADDR;
}
