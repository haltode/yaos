#include <stdint.h>
#include <string.h>

#include <kernel/gdt.h>

Gdt_entry gdt[NB_GDT_ENTRY];
Gdt_ptr gdt_ptr;
extern void gdt_flush(void);

Tss_entry tss;
extern void tss_flush(void);

static void gdt_set_entry(uint8_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity)
{
   gdt[num].base_low = base & 0xFFFF;
   gdt[num].base_middle = (base >> 16) & 0xFF;
   gdt[num].base_high = (base >> 24) & 0xFF;

   gdt[num].limit_low = limit & 0xFFFF;

   gdt[num].granularity = (limit >> 16) & 0xF;
   gdt[num].granularity |= (granularity & 0xF0);

   gdt[num].access = access;
}

static void tss_install(uint8_t num, uint16_t kernel_ss, uint16_t kernel_esp)
{
   uint32_t base = (uint32_t) &tss;
   uint32_t limit = base + sizeof(Tss_entry);

   gdt_set_entry(num, base, limit, 0xE9, 0x0);

   memset(&tss, 0, sizeof(Tss_entry));

   tss.ss0 = kernel_ss;
   tss.esp0 = kernel_esp;

   tss.cs = 0x0B;
   tss.ss = 0x13;
   tss.es = 0x13;
   tss.ds = 0x13;
   tss.fs = 0x13;
   tss.gs = 0x13;
}

void gdt_install(void)
{
   /* NULL descriptor */
   gdt_set_entry(0, 0x0, 0x0, 0x0, 0x0);
   /* Kernel code segment descriptor */
   gdt_set_entry(1, 0x0, 0xFFFFFFFF, 0x9A, 0xCF);
   /* Kernel data segment descriptor */
   gdt_set_entry(2, 0x0, 0xFFFFFFFF, 0x92, 0xCF);
   /* User code segment descriptor */
   gdt_set_entry(3, 0x0, 0xFFFFFFFF, 0xFA, 0xCF);
   /* User data segment descriptor */
   gdt_set_entry(4, 0x0, 0xFFFFFFFF, 0xF2, 0xCF);
   /* Task state register (TSS) */
   tss_install(5, 0x10, 0x0);

   gdt_ptr.limit = (sizeof(Gdt_entry) * NB_GDT_ENTRY) - 1;
   gdt_ptr.base = (uint32_t) &gdt;

   gdt_flush();
   tss_flush();
}
