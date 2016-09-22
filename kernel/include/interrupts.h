#ifndef _KERNEL_INTERRUPTS_H
#define _KERNEL_INTERRUPTS_H

#include <stdint.h>

/* This defines what the stack looks like after an ISR was running */
struct stack
{
   /* Pushed the segs last */
   uint32_t gs, fs, es, ds;
   /* Pushed by 'pusha' */
   uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
   /* Our 'push #' and ecodes do this */
   uint32_t id, err_code;
   /* Pushed by the processor automatically */ 
   uint32_t eip, cs, eflags, useresp, ss;
};

/* IDT */
void idt_set_entry(uint8_t num, uint32_t base, uint16_t selector, uint8_t flags);
void idt_install(void);

/* ISR */
void isr_install(void);

/* IRQ */
void irq_install_handler(uint8_t irq, void (*handler)(struct stack *registers));
void irq_uninstall_handler(uint8_t irq);
void irq_install(void);

#endif
