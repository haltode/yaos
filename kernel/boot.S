/*

#############
# Multiboot #
#############

*/

/* Declare constants for the multiboot header */
.set ALIGN,    1<<0             /* align loaded modules on page boundaries */
.set MEMINFO,  1<<1             /* provide memory map */
.set FLAGS,    ALIGN | MEMINFO  /* this is the Multiboot 'flag' field */
.set MAGIC,    0x1BADB002       /* 'magic number' lets bootloader find the header */
.set CHECKSUM, -(MAGIC + FLAGS) /* checksum of above, to prove we are multiboot */

/* Declare a header as in the Multiboot Standard */
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM


/*

#########
# Stack #
#########

*/

/* Reserve a stack for the initial thread */
.section .stack, "aw", @nobits
stack_bottom:
.skip 16384 /* 16 KiB */
stack_top:


/*

#######################
# Boot page directory #
#######################

*/

/* Our kernel is actually loaded at 1 MiB (physical address) but is
   mapped to 3GB (virtual address) */
.set KERNEL_VIRTUAL_BASE, 0xC0000000  /* 3GB */
/* Page directory index of the kernel's page table entries */
.set KERNEL_PAGE_NUM, (KERNEL_VIRTUAL_BASE >> 22)

/* Set up the boot page directory for 4MB pages */
.section .data
.align 4096
.global boot_page_directory
boot_page_directory:
   /* Unused first entry */
   .long 0x00000083
   /* Empty pages before the kernel */
   .fill (KERNEL_PAGE_NUM - 1), 4, 0x00000000
   /* Kernel's virtual address */
   .long 0x00000083
   /* Empty pages after the kernel */
   .fill (1024 - KERNEL_PAGE_NUM - 1), 4, 0x00000000


/*

################
# Kernel setup #
################

*/

/* Setup function that GRUB will call first */
.section .text
.global loader
loader:
   /* Put the page directory's address in CR3 */
   movl $(boot_page_directory - KERNEL_VIRTUAL_BASE), %ecx
   movl %ecx, %cr3

   /* Set the PSE bit in CR4 to enable 4MB pages */
   movl %cr4, %ecx
   orl $0x00000010, %ecx
   movl %ecx, %cr4

   /* Set the paging enable bit in CR0 */
   movl %cr0, %ecx
   orl $0x80000000, %ecx
   movl %ecx, %cr0

   /* Long jump to the virtual address of start_higher_half */
   lea (start_higher_half), %ecx
   jmp *%ecx


start_higher_half:
   /* Unmap the first identity mapped 4MB of virtual address (we don't
      need it anymore) */
   movl $0x00000000, (boot_page_directory)
   invlpg (0)

   /* Set up the stack */
   movl $stack_top, %esp
   push %esp

   /* Push the address of the multiboot header onto the stack */
   add $KERNEL_VIRTUAL_BASE, %ebx
   push %ebx

   /* Call the global constructors */
   call _init

   /* Transfer control to the main kernel */
   call kernel_main

   /* Hang if kernel_main unexpectedly returns */
   cli
1: hlt
   jmp 1b
