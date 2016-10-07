#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/interrupts.h>
#include <kernel/paging.h>
#include <kernel/timer.h>
#include <kernel/keyboard.h>

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
   irq_install();
   puts("(kernel) IRQ loaded.");

   /* Paging is already enabled because we are using a higher half
      kernel, so we just need to set up others details about it */
   paging_setup();
   puts("(kernel) Paging fully set.");

   timer_install();
   puts("(kernel) Timer enabled.");

   keyboard_install();
   puts("(kernel) Keyboard enabled.");

   puts("");
   puts("Hello kernel World!");

   /* Make sure the main function doesn't exit prematurely 
      (Otherwise it disables interrupts) */
   for(;;)
      asm("hlt");
}
