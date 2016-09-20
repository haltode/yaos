# This will set up our new segment registers. We need to do
# something special in order to set CS. We do what is called a
# far jump. A jump that includes a segment as well as an offset.
.section .text
.global gdt_flush
.type gdt_flush, @function
gdt_flush:
   # Load the GDT with our external pointer 'gdt_ptr' (defined in the C code)
   lgdt gdt_ptr
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
