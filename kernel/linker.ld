/* The bootloader will look at this image and start execution at the symbol
   designated at the entry point. */
ENTRY(loader)

/* Tell where the various sections of the object files will be put in the final
   kernel image. */
SECTIONS
{
   /* This is a higher half kernel, so it will live at 3GB + 1MB in the 
      virtual address space, which will be mapped to 1MB in the 
      physical address space. */
   KERNEL_VIRTUAL_OFFSET = 0xC0000000;

   . = 1M;
   . += KERNEL_VIRTUAL_OFFSET;

   kernel_start = .;

   /* First put the multiboot header, as it is required to be put very early
      early in the image or the bootloader won't recognize the file format.
      Next we'll put the .text section. */
   .text ALIGN(4K) : AT(ADDR(.text) - KERNEL_VIRTUAL_OFFSET)
   {
      *(.multiboot)
      *(.text)
   }

   /* Read-only data */
   .rodata ALIGN(4K) : AT(ADDR(.rodata) - KERNEL_VIRTUAL_OFFSET)
   {
      *(.rodata)
   }

   /* Read-write data (initialized) */
   .data ALIGN(4K) : AT(ADDR(.data) - KERNEL_VIRTUAL_OFFSET)
   {
      *(.data)
   }

   /* Read-write data (uninitialized) and stack */
   .bss ALIGN(4K) : AT(ADDR(.bss) - KERNEL_VIRTUAL_OFFSET)
   {
      *(.bss)
      *(.stack)
   }

   kernel_end = .;
}
