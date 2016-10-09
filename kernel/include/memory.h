#ifndef _KERNEL_MEMORY_H
#define _KERNEL_MEMORY_H

#include <stddef.h>
#include <stdbool.h>

#include <kernel/multiboot.h>
#include <kernel/paging.h>

/* Physical Memory Manager */

void phys_mem_init(multiboot_info_t* boot_info);

void *phys_mem_alloc_frames(size_t size);
void *phys_mem_alloc_frame(void);
void phys_mem_free_frames(void* frames, size_t size);
void phys_mem_free_frame(void* frame);

/* Virtual Memory Manager */

void virt_mem_init(void);

bool virt_mem_alloc_page(uint32_t *pt_entry);
void virt_mem_free_page(uint32_t *pt_entry);

uint32_t *virt_mem_lookup_pt_entry(struct page_table *table, uint32_t address);
uint32_t *virt_mem_lookup_pd_entry(struct page_dir *dir, uint32_t address);
struct page_dir *virt_mem_get_dir(void);

void virt_mem_map_page(void *physical, void *virtual);

void virt_mem_setup_page_table(  struct page_table *table,
                                 uint32_t phys_addr, uint32_t virt_addr);
void virt_mem_setup_page_dir_entry( struct page_dir *dir,
                                    struct page_table *table, uint32_t address);


#endif
