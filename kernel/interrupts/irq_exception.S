.section .text
.align 4

/* IRQ (Interrupt Requests) */

/* Since there is no error code, we use a "dummy error code" of 0 */
.macro IRQ index entry
   .global irq\index
   .type irq\index, @function
   irq\index:
      cli
      push $0x00
      push $\entry
      jmp irq_common_stub
.endm

IRQ 0, 32
IRQ 1, 33
IRQ 2, 34
IRQ 3, 35
IRQ 4, 36
IRQ 5, 37
IRQ 6, 38
IRQ 7, 39
IRQ 8, 40
IRQ 9, 41
IRQ 10, 42
IRQ 11, 43
IRQ 12, 44
IRQ 13, 45
IRQ 14, 46
IRQ 15, 47

/* This is a stub that we have created for IRQ based ISRs. This calls 
   'irq_handler' in our C code (similar to the ISR common stub). */
irq_common_stub:
   /* Push all registers */
   pusha
   /* Push segment registers */
   push %ds
   push %es
   push %fs
   push %gs

   /* Load the Kernel Data Segment descriptor */
   mov $0x10, %ax
   mov %ax, %ds
   mov %ax, %es
   mov %ax, %fs
   mov %ax, %gs
   /* Call the fault handler */
   mov %esp, %eax
   push %eax
   mov $irq_handler, %eax
   /* A special call, preserves the 'eip' register */
   call *%eax
   pop %eax

   /* Restore segment registers */
   pop %gs
   pop %fs
   pop %es
   pop %ds
   popa

   /* Cleans up the pushed error code and pushed IRQ number */
   add $8, %esp
   /* Pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP */
   iret
