#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#include <kernel/interrupts.h>

#define NB_TABLE_ENTRY 1024

/* 3 level paging scheme (4 GiB of memory)

   Page directory = 1024 * Page table
   Page table = 1024 * Page
   Page = 4 KiB of memory

   Linear Address :

   0-11: Offset
   12-21: Table
   22-31: Directory

*/

/* Page directory entry

0: Present
1: Read/write
2: User/supervisor
3: Write through
4: Cache disabled
5: Accessed
6: 0
7: Page size
8: Ignored
9-11: Unused
12-31: Page table address

*/

/* Page table entry

0: Present
1: Read/write
2: User/supervisor
3: Write through
4: Cache disabled
5: Accessed
6: Dirty
7: 0
8: Global
9-11: Unused
12-31: Page address

*/

uint32_t *page_directory;
uint32_t *page_table0;

extern void paging_enable(void);


void page_fault_handler(struct stack *registers)
{
   /* The faulting address is stored in the CR2 register */
   uint32_t faulting_address;
   __asm__ __volatile__ ("mov %%cr2, %0" : "=r" (faulting_address));

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

static void paging_setup(void)
{
   /* Set up a simple page table as an example */

   page_directory[0] = (uint32_t) &page_table0;
   /* 0x3 sets present and read/write bits */
   page_directory[0] |= 0x3;
   /* Set the rest of the page directory as blank entries */
   for(size_t i = 1; i < NB_TABLE_ENTRY; ++i)
      page_directory[i] = 0x0;

   /* Set up our example page table */
   for(size_t i = 0; i < NB_TABLE_ENTRY; ++i) {
      uint32_t page_address = i * (NB_TABLE_ENTRY * 4);
      page_table0[i] = page_address;
      page_table0[i] |= 3;
   }
}

void paging_install(void)
{
   isr_install_handler(14, page_fault_handler);

   paging_setup();
   paging_enable();
}
