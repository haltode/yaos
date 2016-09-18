#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/isr.h>
#include <kernel/irq.h>
#include <kernel/timer.h>

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
   /* Now we can allow IRQs to happen */
   __asm__ __volatile__ ("sti");

   timer_install();
   puts("(kernel) Timer loaded.");

   puts("");
   puts("Hello kernel World!");
}
