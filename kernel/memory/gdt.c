#include <stdint.h>

#define NB_GDT_ENTRY 3

/* GDT entry

00-15: Limit
16-31: Base
32-39: Base
40-47: Access

   0: Accessed bit
   1: Readable bit/Writable bit
   2: Direction bit/Conforming bit
   3: Executable bit
   4: 1
   5-6: Privilege bits
   7: Present bit

48-51: Limit
52-55: Flags

   0: 0
   1: 0
   2: Size bit
   3: Granularity bit

56-63: Base

*/

typedef struct gdt_entry_t Gdt_entry;
struct gdt_entry_t {
   uint16_t limit_low;
   uint16_t base_low;
   uint8_t base_middle;
   uint8_t access;
   uint8_t limit_high : 4;
   uint8_t flags : 4;
   uint8_t base_high;
} __attribute__((packed));

typedef struct gdt_ptr_t Gdt_ptr;
struct gdt_ptr_t {
   uint16_t limit;
   uint32_t base;
} __attribute__((packed));


Gdt_entry gdt[NB_GDT_ENTRY];
Gdt_ptr gdt_ptr;

extern void gdt_flush(void);


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
   gdt_ptr.limit = (sizeof(Gdt_entry) * NB_GDT_ENTRY) - 1;
   gdt_ptr.base = (uint32_t) &gdt;

   /* Flush out the old GDT and install the new one */
   gdt_flush();
}
