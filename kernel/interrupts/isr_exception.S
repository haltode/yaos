.section .text
.align 4

/* ISR (Interrupt Service Routines) */

/* When there is no error code, we use a "dummy error code" of 0 */
.macro ISR_NO_ERR index
   .global isr\index
   isr\index:
      cli
      push $0
      push $\index
      jmp isr_common_stub
.endm

.macro ISR_ERR index
   .global isr\index
   isr\index:
      cli
      push $\index
      jmp isr_common_stub
.endm

/* Division By Zero Exception */
ISR_NO_ERR 0
/* Debug Exception */
ISR_NO_ERR 1
/* Non Maskable Interrupt Exception */
ISR_NO_ERR 2
/* Breakpoint Exception */
ISR_NO_ERR 3
/* Into Detected Overflow Exception */
ISR_NO_ERR 4
/* Out of Bounds Exception */
ISR_NO_ERR 5
/* Invalid Opcode Exception */
ISR_NO_ERR 6
/* No Coprocessor Exception */
ISR_NO_ERR 7
/* Double Fault Exception */
ISR_ERR 8
/* Coprocessor Segment Overrun Exception */
ISR_NO_ERR 9
/* Bad TSS Exception */
ISR_ERR 10
/* Segment Not Present Exception */
ISR_ERR 11
/* Stack Fault Exception */
ISR_ERR 12
/* General Protection Fault Exception */
ISR_ERR 13
/* Page Fault Exception */
ISR_ERR 14
/* Unknown Interrupt Exception */
ISR_NO_ERR 15
/* Coprocessor Fault Exception */
ISR_NO_ERR 16
/* Alignment Check Exception */
ISR_NO_ERR 17
/* Machine Check Exception */
ISR_NO_ERR 18
/* All the others are reserved */
ISR_NO_ERR 19
ISR_NO_ERR 20
ISR_NO_ERR 21
ISR_NO_ERR 22
ISR_NO_ERR 23
ISR_NO_ERR 24
ISR_NO_ERR 25
ISR_NO_ERR 26
ISR_NO_ERR 27
ISR_NO_ERR 28
ISR_NO_ERR 29
ISR_NO_ERR 30
ISR_NO_ERR 31
/* Syscall */
ISR_NO_ERR 128

/* This is our common ISR stub. It saves the processor state, sets 
   up for kernel mode segments, calls the C-level fault handler, 
   and finally restores the stack frame. */
isr_common_stub:
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
   mov $fault_handler, %eax
   /* A special call, preserves the 'eip' register */
   call *%eax
   pop %eax

   /* Restore segment registers */
   pop %gs
   pop %fs
   pop %es
   pop %ds
   popa

   /* Cleans up the pushed error code and pushed ISR number */
   add $8, %esp
   /* Pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP */
   iret
