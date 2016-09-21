#include <stdint.h>

#include <kernel/interrupts.h>
#include <kernel/io.h>

extern void outb(uint32_t port, uint8_t val);
extern uint8_t inb(uint32_t port);

#define NB_IRQ_ROUTINES 16

/* IRQ (Interrupt Requests) */
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

/* This array is actually an array of function pointers. We use 
   this to handle custom IRQ handlers for a given IRQ */
void *irq_routines[NB_IRQ_ROUTINES] =
{
   0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0
};

/* Install a custom IRQ handler for the given IRQ */
void irq_install_handler(uint8_t irq, void (*handler)(struct stack *registers))
{
   irq_routines[irq] = handler;
}

void irq_uninstall_handler(uint8_t irq)
{
   irq_routines[irq] = 0;
}

/* Normally, IRQs 0 to 7 are mapped to entries 8 to 15. This is a problem
   in protected mode, because IDT entry 8 is a Double Fault!
   Without remapping, every time IRQ0 fires, you get a Double Fault
   Exception, which is NOT actually what's happening. 
   We send commands to the Programmable Interrupt Controller 
   (PICs - also called the 8259's) in order to make IRQ0 to 15 be
   remapped to IDT entries 32 to 47 */
void irq_remap(void)
{
   outb(0x20, 0x11);
   outb(0xA0, 0x11);
   outb(0x21, 0x20);
   outb(0xA1, 0x28);
   outb(0x21, 0x04);
   outb(0xA1, 0x02);
   outb(0x21, 0x01);
   outb(0xA1, 0x01);
   outb(0x21, 0x00);
   outb(0xA1, 0x00);
}

void irq_install(void)
{
   /* Remap the interrupt controllers */
   irq_remap();

   /* Install the ISRs */
   idt_set_entry(32, (uint32_t)irq0, 0x08, 0x8E);
   idt_set_entry(33, (uint32_t)irq1, 0x08, 0x8E);
   idt_set_entry(34, (uint32_t)irq2, 0x08, 0x8E);
   idt_set_entry(35, (uint32_t)irq3, 0x08, 0x8E);
   idt_set_entry(36, (uint32_t)irq4, 0x08, 0x8E);
   idt_set_entry(37, (uint32_t)irq5, 0x08, 0x8E);
   idt_set_entry(38, (uint32_t)irq6, 0x08, 0x8E);
   idt_set_entry(39, (uint32_t)irq7, 0x08, 0x8E);
   idt_set_entry(40, (uint32_t)irq8, 0x08, 0x8E);
   idt_set_entry(41, (uint32_t)irq9, 0x08, 0x8E);
   idt_set_entry(42, (uint32_t)irq10, 0x08, 0x8E);
   idt_set_entry(43, (uint32_t)irq11, 0x08, 0x8E);
   idt_set_entry(44, (uint32_t)irq12, 0x08, 0x8E);
   idt_set_entry(45, (uint32_t)irq13, 0x08, 0x8E);
   idt_set_entry(46, (uint32_t)irq14, 0x08, 0x8E);
   idt_set_entry(47, (uint32_t)irq15, 0x08, 0x8E);
}

/* Each of the IRQ ISRs point to this function, rather than
   the 'fault_handler' in 'isr.c'. The IRQ Controllers need
   to be told when you are done servicing them, so you need
   to send them an "End of Interrupt" command (0x20). There
   are two 8259 chips: The first exists at 0x20, the second
   exists at 0xA0. If the second controller (an IRQ from 8 to
   15) gets an interrupt, you need to acknowledge the
   interrupt at BOTH controllers, otherwise, you only send
   an EOI command to the first controller. If you don't send
   an EOI, you won't raise any more IRQs */
void irq_handler(struct stack *registers)
{
   /* This is a blank function pointer */
   void (*handler)(struct stack *registers);

   /* Find out if we have a custom handler to run for this IRQ and run it */
   handler = irq_routines[registers->id - 32];
   if(handler)
      handler(registers);

   /* If the IDT entry that was invoked was greater than 40
      (meaning IRQ8 - IRQ15), then we need to send an EOI to
      the slave controller */
   if(registers->id >= 40)
      outb(0xA0, 0x20);

   /* In either case, we need to send an EOI to the master
      interrupt controller too */
   outb(0x20, 0x20);
}
