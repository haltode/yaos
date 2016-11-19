#ifndef _KERNEL_MEMORY_H
#define _KERNEL_MEMORY_H

#include <stdbool.h>
#include <stddef.h>

#include <kernel/multiboot.h>
#include <kernel/paging.h>

/*
 * Physical Memory Manager
 */

#define FRAME_PER_BYTE     8
#define FRAME_SIZE         4096

void phys_mem_init(Multiboot_info *boot_info);

void *phys_mem_alloc_frames(size_t size);
void *phys_mem_alloc_frame(void);
void phys_mem_free_frames(void *frames, size_t size);
void phys_mem_free_frame(void *frame);

/*
 * Virtual Memory Manager
 */

void virt_mem_init(void);

bool virt_mem_alloc_page(uint32_t *pt_entry);
void virt_mem_free_page(uint32_t *pt_entry);

void virt_mem_map_page(void *physical, void *virtual);
void virt_mem_unmap_page(void *virtual);

Page_dir *virt_mem_get_dir(void);
void virt_mem_setup_page_dir_entry( Page_dir *dir,
                                    Page_table *table, uint32_t address);
void virt_mem_switch_page_dir(Page_dir *dir);

void virt_mem_flush_tlb(void);
void virt_mem_flush_tlb_entry(void *address);

/*
 * Heap Manager
 */

/* The kernel heap is located at 512 MiB and expands to 1 GiB */
#define KERNEL_HEAP_ADDR   0x20000000
#define KERNEL_HEAP_SIZE   0x20000000

void heap_init(void);

#endif
