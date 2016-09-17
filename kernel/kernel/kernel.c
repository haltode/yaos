#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/isr.h>

void kernel_main(void)
{
   terminal_initialize();
   puts("(kernel) TTY loaded.");

   gdt_install();
   puts("(kernel) GDT loaded.");

   idt_install();
   puts("(kernel) IDT loaded.");

   isr_install();
   puts("(kernel) ISR loaded.");

   puts("");
   puts("Hello kernel World!");
}
