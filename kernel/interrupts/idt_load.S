.section .text
.align 4

/* IDT (Interrupt Descriptor Table) */

.global idt_load
.type idt_load, @function
idt_load:
   /* The pointer 'idt_ptr' is defined in the C code */
   lidt idt_ptr
   ret
