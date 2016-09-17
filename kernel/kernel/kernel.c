#include <stdio.h>

#include <kernel/gdt.h>
#include <kernel/tty.h>

void kernel_main(void)
{
   terminal_initialize();
   puts("(kernel) TTY loaded.");

   gdt_install();
   puts("(kernel) GDT loaded.");

   puts("Hello kernel World!");
}
