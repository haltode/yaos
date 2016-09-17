#ifndef ARCH_I386_IDT_H
#define ARCH_I386_IDT_H

#include <stdint.h>

/* We are only using the first 32 entries here, but if any undefined IDT entry
   is hit, it will cause an "Unhandled Interrupt" exception */
#define NB_IDT_ENTRY 256

/* IDT entry

00-15: Offset
16-31: Selector
32-39: Unused
40-47: Flags (Type/Attributes)

   0-3: Gate type
   4: S (Storage segment)
   5-6: DPL (Descriptor Privilege Level)
   7: P (Present)

48-63: Offset

*/

struct idt_entry {
   uint16_t offset_low;
   uint16_t selector;
   uint8_t unused;
   uint8_t flags;
   uint16_t offset_high;
} __attribute__((packed));

struct idt_ptr {
   uint16_t limit;
   uint32_t base;
} __attribute__((packed));

#endif
