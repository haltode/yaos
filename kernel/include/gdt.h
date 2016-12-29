#ifndef _KERNEL_GDT_H
#define _KERNEL_GDT_H

#include <stdint.h>

#define NB_GDT_ENTRY 6

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
   uint8_t granularity;
   uint8_t base_high;
} __attribute__((packed));

typedef struct gdt_ptr_t Gdt_ptr;
struct gdt_ptr_t {
   uint16_t limit;
   uint32_t base;
} __attribute__((packed));

/* TODO: more info about TSS structure */

typedef struct tss_entry_t Tss_entry;
struct tss_entry_t {
   uint32_t prevTss;
   uint32_t esp0;
   uint32_t ss0;
   uint32_t esp1;
   uint32_t ss1;
   uint32_t esp2;
   uint32_t ss2;
   uint32_t cr3;
   uint32_t eip;
   uint32_t eflags;
   uint32_t eax;
   uint32_t ecx;
   uint32_t edx;
   uint32_t ebx;
   uint32_t esp;
   uint32_t ebp;
   uint32_t esi;
   uint32_t edi;
   uint32_t es;
   uint32_t cs;
   uint32_t ss;
   uint32_t ds;
   uint32_t fs;
   uint32_t gs;
   uint32_t ldt;
   uint16_t trap;
   uint16_t iomap;
} __attribute__((packed));


void gdt_install(void);

#endif
