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

######################
# Higher half kernel #
######################

*/

.section .bss, "aw", @nobits
   .align 4096 /* 4 KiB */
boot_page_directory:
   .skip 4096
boot_page_table:
   .skip 4096

/* The first page table (we use 4 KiB pages) :

0-255    (1 MiB): Identity mapped address
256-1023 (3 MiB): Kernel

*/

.section .text

/* The kernel is physically located at 1 MiB but it's mapped to
   the virtual address of 3 GiB (it's a higher half kernel) */
.set KERNEL_VIRTUAL_BASE, 0xC0000000

/* Setup function that GRUB will call first */
.global loader
.type loader, @function
loader:
   movl $(boot_page_directory - KERNEL_VIRTUAL_BASE), %edi

   /* The first 1 MiB is identity mapped */
   movl $(boot_page_table - KERNEL_VIRTUAL_BASE), %edx
   /* 0x003 sets present and read/write bits */
   orl $0x003, %edx
   movl %edx, (%edi)

   /* 768th entry in the page directory = kernel
      768 corresponds to our kernel virtual base address */
   movl $(boot_page_directory - KERNEL_VIRTUAL_BASE + 0xC00), %edi
   orl $0x003, %edx
   movl %edx, (%edi)

   /* Fill in the page table */
   movl $(boot_page_table - KERNEL_VIRTUAL_BASE), %edi
   movl $0x0, %ecx

setup_entry:
   movl %ecx, %edx
   /* Get the page number */
   shll $12, %edx
   /* 0x003 sets present and read/write bits */
   orl $0x003, %edx

   /* (%edi, %ecx, 4) = (%edi + %ecx * 4) */
   movl %edx, (%edi, %ecx, 4)

   incl %ecx
   /* 1024 = 4 MiB (the end of the page table) */
   cmpl $1024, %ecx
   jne setup_entry

setup_paging:
   /* Put the page directory's address in CR3 */
   movl $(boot_page_directory - KERNEL_VIRTUAL_BASE), %ecx
   movl %ecx, %cr3

   /* Set the paging enable bit in CR0 */
   movl %cr0, %ecx
   orl $0x80000000, %ecx
   movl %ecx, %cr0

   /* Long jump to the virtual address of start_higher_half */
   lea (start_higher_half), %ecx
   jmp *%ecx

start_higher_half:
   /* Unmap the first identity mapped 4MB of virtual address
      (we don't need it anymore) */
   movl $0x0, (boot_page_directory)
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
