#include <stdint.h>

#define NB_GDT_ENTRY 3

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

struct gdt_entry {
   uint16_t limit_low;
   uint16_t base_low;
   uint8_t base_middle;
   uint8_t access;
   uint8_t limit_high : 4;
   uint8_t flags : 4;
   uint8_t base_high;
} __attribute__((packed));

struct gdt_ptr {
   uint16_t limit;
   uint32_t base;
} __attribute__((packed));


struct gdt_entry gdt[NB_GDT_ENTRY];
struct gdt_ptr gdt_ptr;

extern void gdt_flush();


static void gdt_set_entry(uint8_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags)
{
   gdt[num].base_low = base & 0xFFFF;
   gdt[num].base_middle = (base >> 16) & 0xFF;
   gdt[num].base_high = (base >> 24) & 0xFF;

   gdt[num].limit_low = limit & 0xFFFF;
   gdt[num].limit_high = (limit >> 16) & 0xF;

   gdt[num].access = access;
   gdt[num].flags = flags;
}

void gdt_install(void)
{
   /* NULL descriptor */
   gdt_set_entry(0, 0x0, 0x0, 0x0, 0x0);
   /* Code segment descriptor */
   gdt_set_entry(1, 0x0, 0xFFFFFFFF, 0x9A, 0xC);
   /* Data segment descriptor */
   gdt_set_entry(2, 0x0, 0xFFFFFFFF, 0x92, 0xC);

   /* Setup our GDT pointer */
   gdt_ptr.limit = (sizeof(struct gdt_entry) * NB_GDT_ENTRY) - 1;
   gdt_ptr.base = &gdt;

   /* Flush out the old GDT and install the new one */
   gdt_flush();
}
