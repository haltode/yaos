.section .text
.align 4

.global load_page_directory
.type load_page_directory, @function
load_page_directory:
   /* Put the physical address of the first page directory entry in CR3 */
   movl current_dir_base_reg, %eax
   movl %eax, %cr3
   ret

.global enable_paging
.type enable_paging, @function
enable_paging:
   /* Set the paging enable bit in CR0 */
   movl %cr0, %eax
   orl $0x80000000, %eax
   movl %eax, %cr0
   ret
