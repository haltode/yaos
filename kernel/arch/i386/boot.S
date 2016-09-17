# Declare constants for the multiboot header
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

# Declare a header as in the Multiboot Standard
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Reserve a stack for the initial thread
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

# The kernel entry point
.section .text
.global _start
.type _start, @function
_start:
   movl $stack_top, %esp

   # Call the global constructors
   call _init
   
   # Transfer control to the main kernel
   call kernel_main

   # Hang if kernel_main unexpectedly returns
   cli
1: hlt
   jmp 1b
.size _start, . - _start

# GDT related code
# This will set up our new segment registers. We need to do
# something special in order to set CS. We do what is called a
# far jump. A jump that includes a segment as well as an offset.
.section .text
.global gdt_flush
.type gdt_flush, @function
gdt_flush:
   # Load the GDT with our 'gp' which is a special pointer
   lgdt gp
   # 0x08 is the offset to our code segment: far jump
   jmp $0x08, $reload_cs

   reload_cs:
      # 0x10 is the offset in the GDT to our data segment
      movw $0x10, %ax
      movw %ax, %ds
      movw %ax, %es
      movw %ax, %fs
      movw %ax, %gs
      movw %ax, %ss
      ret
