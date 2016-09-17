#ifndef ARCH_I386_GDT_H
#define ARCH_I386_GDT_H

#include <stdint.h>

#define NB_ENTRY_GDT 3

/* GDT entry

00-15: Limit
16-31: Base
32-39: Base
40-47: Access

   0: AC (Accessed bit)
   1: RW (Readable bit/Writable bit)
   2: DC (Direction bit/Conforming bit)
   3: Ex (Executable bit)
   4: 1
   5-6: Privl (Privilege bits)
   7: Pr (Present bit)

48-51: Limit
52-55: Flags

   0: 0
   1: 0
   2: Sz (Size bit)
   3: Gr (Granularity bit)

56-63: Base

*/

/* We use the 'packed' attribute to prevent the compiler from optimizing the
   structure */
struct gdt_entry {
   uint16_t limit_low;
   uint16_t base_low;
   uint8_t base_middle;
   uint8_t access;
   uint8_t limit_high : 4;
   uint8_t flags : 4;
   uint8_t base_high;
} __attribute__((packed));

/* GDT's pointer which includes the limit: the max bytes taken up by the GDT
   minus 1 */
struct gdt_ptr {
   uint16_t limit;
   uint32_t base;
} __attribute__((packed));

#endif
