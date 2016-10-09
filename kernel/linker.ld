/* The bootloader will look at this image and start execution at the symbol
   designated at the entry point. */
ENTRY(loader)

/* Tell where the various sections of the object files will be put in the final
   kernel image. */
SECTIONS
{
   /* The kernel is situated at 1 MiB */
   . = 1M;

   kernel_start = .;

   /* First put the multiboot header, as it is required to be put very early
      early in the image or the bootloader won't recognize the file format.
      Next we'll put the .text section. */
   .text BLOCK(4K) : ALIGN(4K)
   {
      *(.multiboot)
      *(.text)
   }

   /* Read-only data */
   .rodata BLOCK(4K) : ALIGN(4K)
   {
      *(.rodata)
   }

   /* Read-write data (initialized) */
   .data BLOCK(4K) : ALIGN(4K)
   {
      *(.data)
   }

   /* Read-write data (uninitialized) and stack */
   .bss BLOCK(4K) : ALIGN(4K)
   {
      *(.bss)
      *(.stack)
   }

   kernel_end = .;
}
