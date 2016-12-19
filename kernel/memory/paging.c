#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include <kernel/interrupts.h>
#include <kernel/paging.h>

/*
 * Setup
 */

void page_fault_handler(Stack *registers)
{
   /* The faulting address is stored in the CR2 register */
   uint32_t faulting_address;
   asm ("mov %%cr2, %0" : "=r" (faulting_address));

   /* The error code gives us details of what happened */
   uint8_t present = !(registers->err_code & 0x1);
   uint8_t read_write = registers->err_code & 0x2;
   uint8_t user = registers->err_code & 0x4;
   uint8_t reserved = registers->err_code & 0x8;

   printf("Page fault ( ");
   if(present)    printf("present ");
   if(read_write) printf("read-only ");
   if(user)       printf("user-mode ");
   if(reserved)   printf("reserved ");
   printf(") at 0x%x\n", faulting_address);
}

void paging_setup(void)
{
   /* Add a custom ISR handler for the 'Page Fault' exception */
   isr_install_handler(14, page_fault_handler);
}

/* 3 level paging scheme (4 GiB of memory)

   Page directory = 1024 * Page tables
   Page table = 1024 * Pages
   Page = 4 KiB of memory

| Bits  | Page directory entry | Page table entry |
| ----  | -------------------- | ---------------- |
| 0     | Present              | Present          |
| 1     | Read/write           | Read/write       |
| 2     | User/supervisor      | User/supervisor  |
| 3     | Write through        | Write through    |
| 4     | Cache disabled       | Cache disabled   |
| 5     | Accessed             | Accessed         |
| 6     | 0                    | Dirty            |
| 7     | Page size            | 0                |
| 8     | Ignored              | Global           |
| 9-11  | Unused               | Unused           |
| 12-31 | Page table address   | Page address     |

*/

/*
 * Page directory
 */

void pd_entry_add_flags(uint32_t *pd_entry, uint32_t flags)
{
   assert(pd_entry != NULL);
   *pd_entry |= flags;
}

void pd_entry_del_flags(uint32_t *pd_entry, uint32_t flags)
{
   assert(pd_entry != NULL);
   *pd_entry &= ~flags;
}

void pd_entry_set_frame(uint32_t *pd_entry, uint32_t address)
{
   assert(pd_entry != NULL);
   *pd_entry = (*pd_entry & ~PDE_FRAME_BIT) | address;
}

uint32_t pd_entry_get_frame(uint32_t pd_entry)
{
   return pd_entry & PDE_FRAME_BIT;
}

bool pd_entry_is_present(uint32_t pd_entry)
{
   return pd_entry & PDE_PRESENT_BIT;
}

bool pd_entry_is_writable(uint32_t pd_entry)
{
   return pd_entry & PDE_WRITABLE_BIT;
}

uint32_t pd_index(uint32_t virt_addr)
{
   return virt_addr >> 22;
}

uint32_t pd_entry_phys_addr(uint32_t *pd_entry)
{
   assert(pd_entry != NULL);
   return *pd_entry & ~0xFFF;
}

/*
 * Page table
 */

void pt_entry_add_flags(uint32_t *pt_entry, uint32_t flags)
{
   assert(pt_entry != NULL);
   *pt_entry |= flags;
}

void pt_entry_del_flags(uint32_t *pt_entry, uint32_t flags)
{
   assert(pt_entry != NULL);
   *pt_entry &= ~flags;
}

void pt_entry_set_frame(uint32_t *pt_entry, uint32_t address)
{
   assert(pt_entry != NULL);
   *pt_entry = (*pt_entry & ~PTE_FRAME_BIT) | address;
}

uint32_t pt_entry_get_frame(uint32_t pt_entry)
{
   return pt_entry & PTE_FRAME_BIT;
}

bool pt_entry_is_present(uint32_t pt_entry)
{
   return pt_entry & PTE_PRESENT_BIT;
}

bool pt_entry_is_writable(uint32_t pt_entry)
{
   return pt_entry & PTE_WRITABLE_BIT;
}

uint32_t pt_index(uint32_t virt_addr)
{
   return (virt_addr >> 12) & 0x3FF;
}
