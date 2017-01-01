#include <stdint.h>
#include <string.h>

#include <kernel/interrupts.h>

Idt_entry idt[NB_IDT_ENTRY];
Idt_ptr idt_ptr;

extern void idt_load(void);

void idt_set_entry(uint8_t num, uint32_t base, uint16_t selector, uint8_t flags)
{
   idt[num].offset_low = base & 0xFFFF;
   idt[num].offset_high = (base >> 16) & 0xFFFF;

   idt[num].selector = selector;

   idt[num].unused = 0x0;

   idt[num].flags = flags | 0x60;
}

void idt_install(void)
{
   /* Setup our IDT pointer */
   idt_ptr.limit = (sizeof(Idt_entry) * NB_IDT_ENTRY) - 1;
   idt_ptr.base = (uint32_t) &idt;

   /* Clear out the entire IDT, initializing it to zeros */
   memset(&idt, 0, sizeof(Idt_entry) * NB_IDT_ENTRY);

   /* Load our new IDT */
   idt_load();
}
