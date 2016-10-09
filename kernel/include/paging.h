#ifndef _KERNEL_PAGING_H
#define _KERNEL_PAGING_H

#include <stdint.h>
#include <stdbool.h>

#define PDE_PRESENT_BIT       0x1
#define PDE_WRITABLE_BIT      0x2
#define PDE_FRAME_BIT         0x7FFFF000

#define PTE_PRESENT_BIT       0x1
#define PTE_WRITABLE_BIT      0x2
#define PTE_FRAME_BIT         0x7FFFF000

#define ENTRY_PER_TABLE 1024
#define ENTRY_PER_DIR   1024

/* 4 KiB */
#define PAGE_SIZE 4096


void paging_setup(void);

/* Page directory */

struct page_dir {
   uint32_t entry[ENTRY_PER_DIR];
};

void pd_entry_add_flags(uint32_t *pd_entry, uint32_t flags);
void pd_entry_del_flags(uint32_t *pd_entry, uint32_t flags);
void pd_entry_set_frame(uint32_t *pd_entry, uint32_t address);
uint32_t pd_entry_get_frame(uint32_t pd_entry);
bool pd_entry_is_present(uint32_t pd_entry);
bool pd_entry_is_writable(uint32_t pd_entry);

/* Page table */

struct page_table {
   uint32_t entry[ENTRY_PER_TABLE];
};

void pt_entry_add_flags(uint32_t *pt_entry, uint32_t flags);
void pt_entry_del_flags(uint32_t *pt_entry, uint32_t flags);
void pt_entry_set_frame(uint32_t *pt_entry, uint32_t address);
uint32_t pt_entry_get_frame(uint32_t pt_entry);
bool pt_entry_is_present(uint32_t pt_entry);
bool pt_entry_is_writable(uint32_t pt_entry);

#endif
