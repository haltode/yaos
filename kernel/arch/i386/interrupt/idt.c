#include <stdint.h>
#include <string.h>

#include "idt.h"

struct idt_entry idt[NB_IDT_ENTRY];
struct idt_ptr idt_ptr;

extern void idt_load();

void idt_set_entry(uint8_t num, uint32_t base, uint16_t selector, uint8_t flags)
{
   idt[num].offset_low = base & 0xFFFF;
   idt[num].offset_high = (base >> 16) & 0xFFFF;

   idt[num].selector = selector;

   idt[num].unused = 0x0;

   idt[num].flags = flags;
}

void idt_install(void)
{
   /* Clear out the entire IDT, initializing it to zeros */
   memset(&idt, 0, sizeof(struct idt_entry) * NB_IDT_ENTRY);

   /* Setup our IDT pointer */
   idt_ptr.limit = (sizeof(struct idt_entry) * NB_IDT_ENTRY) - 1;
   idt_ptr.base = &idt;

   /* Load our new IDT */
   idt_load();
}
