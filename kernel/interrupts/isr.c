#include <stdio.h>

#include <kernel/interrupts.h>

/* ISR (Interrupt Service Routines) */
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

void isr_install(void)
{
   idt_set_entry(0, (uint32_t)isr0, 0x08, 0x8E);
   idt_set_entry(1, (uint32_t)isr1, 0x08, 0x8E);
   idt_set_entry(2, (uint32_t)isr2, 0x08, 0x8E);
   idt_set_entry(3, (uint32_t)isr3, 0x08, 0x8E);
   idt_set_entry(4, (uint32_t)isr4, 0x08, 0x8E);
   idt_set_entry(5, (uint32_t)isr5, 0x08, 0x8E);
   idt_set_entry(6, (uint32_t)isr6, 0x08, 0x8E);
   idt_set_entry(7, (uint32_t)isr7, 0x08, 0x8E);

   idt_set_entry(8, (uint32_t)isr8, 0x08, 0x8E);
   idt_set_entry(9, (uint32_t)isr9, 0x08, 0x8E);
   idt_set_entry(10, (uint32_t)isr10, 0x08, 0x8E);
   idt_set_entry(11, (uint32_t)isr11, 0x08, 0x8E);
   idt_set_entry(12, (uint32_t)isr12, 0x08, 0x8E);
   idt_set_entry(13, (uint32_t)isr13, 0x08, 0x8E);
   idt_set_entry(14, (uint32_t)isr14, 0x08, 0x8E);
   idt_set_entry(15, (uint32_t)isr15, 0x08, 0x8E);

   idt_set_entry(16, (uint32_t)isr16, 0x08, 0x8E);
   idt_set_entry(17, (uint32_t)isr17, 0x08, 0x8E);
   idt_set_entry(18, (uint32_t)isr18, 0x08, 0x8E);
   idt_set_entry(19, (uint32_t)isr19, 0x08, 0x8E);
   idt_set_entry(20, (uint32_t)isr20, 0x08, 0x8E);
   idt_set_entry(21, (uint32_t)isr21, 0x08, 0x8E);
   idt_set_entry(22, (uint32_t)isr22, 0x08, 0x8E);
   idt_set_entry(23, (uint32_t)isr23, 0x08, 0x8E);

   idt_set_entry(24, (uint32_t)isr24, 0x08, 0x8E);
   idt_set_entry(25, (uint32_t)isr25, 0x08, 0x8E);
   idt_set_entry(26, (uint32_t)isr26, 0x08, 0x8E);
   idt_set_entry(27, (uint32_t)isr27, 0x08, 0x8E);
   idt_set_entry(28, (uint32_t)isr28, 0x08, 0x8E);
   idt_set_entry(29, (uint32_t)isr29, 0x08, 0x8E);
   idt_set_entry(30, (uint32_t)isr30, 0x08, 0x8E);
   idt_set_entry(31, (uint32_t)isr31, 0x08, 0x8E);
}

static const char *exception_messages[] =
{
   "Division By Zero",
   "Debug",
   "Non Maskable Interrupt",
   "Breakpoint",
   "Into Detected Overflow",
   "Out of Bounds",
   "Invalid Opcode",
   "No Coprocessor",

   "Double Fault",
   "Coprocessor Segment Overrun",
   "Bad TSS",
   "Segment Not Present",
   "Stack Fault",
   "General Protection Fault",
   "Page Fault",
   "Unknown Interrupt",

   "Coprocessor Fault",
   "Alignment Check",
   "Machine Check",
   "Reserved",
   "Reserved",
   "Reserved",
   "Reserved",
   "Reserved",

   "Reserved",
   "Reserved",
   "Reserved",
   "Reserved",
   "Reserved",
   "Reserved",
   "Reserved",
   "Reserved"
};

/*  All ISRs disable interrupts while they are being serviced as a 'locking'
    mechanism to prevent an IRQ from happening and messing up kernel data
    structures */
void fault_handler(struct stack *registers)
{
   /* We only use the first 32 ISR */
   if(registers->id < 32) {
      puts(exception_messages[registers->id]);
      puts("Exception. System Halted!");
      for(;;);
   }
}
