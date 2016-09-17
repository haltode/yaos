#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>

void kernel_main(void)
{
   terminal_initialize();
   puts("(kernel) TTY loaded.");

   gdt_install();
   puts("(kernel) GDT loaded.");

   idt_install();
   puts("(kernel) IDT loaded.");

   puts("Hello kernel World!");
}
