#include <stdio.h>

#include <kernel/multiboot.h>
#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/interrupts.h>
#include <kernel/memory.h>
#include <kernel/timer.h>
#include <kernel/keyboard.h>

void kernel_main(multiboot_info_t* boot_info)
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

   phys_mem_init(boot_info);
   puts("(kernel) Physical memory manager enabled.");

   virt_mem_init();
   puts("(kernel) Virtual memory manager enabled.");

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
