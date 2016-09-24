.section .text
.align 4

/* IDT (Interrupt Descriptor Table) */

.global idt_load
.type idt_load, @function
idt_load:
   /* Load the IDT with our external pointer 'idt_ptr' (defined in the C code) */
   lidt idt_ptr
   ret
