/* Provided by: https://www.gnu.org/software/grub/manual/multiboot/html_node/multiboot.h.html */
#ifndef _KERNEL_MULTIBOOT_H
#define _KERNEL_MULTIBOOT_H

#ifndef ASM

/* The symbol table for a.out */
typedef struct aout_symbol_table_t Aout_symbol_table;
struct aout_symbol_table_t
{
   unsigned long tabsize;
   unsigned long strsize;
   unsigned long addr;
   unsigned long reserved;
};

/* The section header table for ELF */
typedef struct elf_section_header_table_t Elf_section_header_table;
struct elf_section_header_table_t
{
   unsigned long num;
   unsigned long size;
   unsigned long addr;
   unsigned long shndx;
};

/* The Multiboot information */
typedef struct multiboot_info_t Multiboot_info;
struct multiboot_info_t
{
   unsigned long flags;
   unsigned long mem_lower;
   unsigned long mem_upper;
   unsigned long boot_device;
   unsigned long cmdline;
   unsigned long mods_count;
   unsigned long mods_addr;
   union
   {
      Aout_symbol_table aout_sym;
      Elf_section_header_table elf_sec;
   } u;
   unsigned long mmap_length;
   unsigned long mmap_addr;
};

/* The memory map. Be careful that the offset 0 is base_addr_low but no size */
typedef struct memory_map_t Memory_map;
struct memory_map_t
{
   unsigned long size;
   unsigned long base_addr_low;
   unsigned long base_addr_high;
   unsigned long length_low;
   unsigned long length_high;
   unsigned long type;
};

#endif
#endif
