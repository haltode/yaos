#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#include <kernel/interrupts.h>

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

void page_fault_handler(struct stack *registers)
{
   /* The faulting address is stored in the CR2 register */
   uint32_t faulting_address;
   __asm__ ("mov %%cr2, %0" : "=r" (faulting_address));

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
