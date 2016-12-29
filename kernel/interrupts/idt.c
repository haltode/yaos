#include <stdint.h>
#include <string.h>

/* We are only using the first 32 entries here, but if any undefined IDT entry
   is hit, it will cause an "Unhandled Interrupt" exception */
#define NB_IDT_ENTRY 256

/* IDT entry

00-15: Offset
16-31: Selector
32-39: Unused
40-47: Flags (Type/Attributes)

   0-3: Gate type
   4: Storage segment
   5-6: Descriptor Privilege Level
   7: Present

48-63: Offset

*/

typedef struct idt_entry_t Idt_entry;
struct idt_entry_t {
   uint16_t offset_low;
   uint16_t selector;
   uint8_t unused;
   uint8_t flags;
   uint16_t offset_high;
} __attribute__((packed));

typedef struct idt_ptr_t Idt_ptr;
struct idt_ptr_t {
   uint16_t limit;
   uint32_t base;
} __attribute__((packed));


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
