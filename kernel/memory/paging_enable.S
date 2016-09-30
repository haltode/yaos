.section .text
.align 4

.global paging_enable
.type paging_enable, @function
paging_enable:
   /* Load CR3 with the address of the page directory */
   mov page_directory, %eax
   mov %eax, %cr3

   /* Set the paging bit of CR0 */
   mov %cr0, %eax
   or $0x80000000, %eax
   mov %eax, %cr0

   ret
