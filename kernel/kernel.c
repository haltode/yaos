#include <stdio.h>

#include <kernel/gdt.h>
#include <kernel/interrupts.h>
#include <kernel/keyboard.h>
#include <kernel/memory.h>
#include <kernel/multiboot.h>
#include <kernel/ramdisk.h>
#include <kernel/timer.h>
#include <kernel/tty.h>

Multiboot_info *boot_info;

void kernel_main(Multiboot_info *args)
{
   boot_info = args;

   terminal_init();
   puts("(kernel) TTY loaded.");

   gdt_install();
   puts("(kernel) GDT loaded.");

   idt_install();
   puts("(kernel) IDT loaded.");
   isr_install();
   puts("(kernel) ISR loaded.");
   irq_install();
   puts("(kernel) IRQ loaded.");

   phys_mem_init();
   puts("(kernel) Physical memory manager enabled.");

   virt_mem_init();
   puts("(kernel) Virtual memory manager enabled.");

   heap_init();
   puts("(kernel) Heap manager enabled.");

   timer_install();
   puts("(kernel) Timer enabled.");

   keyboard_install();
   puts("(kernel) Keyboard enabled.");

   ramdisk_init();
   puts("(kernel) Ramdisk initialized.");
   
   puts("");
   puts("Hello kernel World!");

   /* Make sure the main function doesn't exit prematurely 
      (Otherwise it disables interrupts) */
   for(;;)
      asm("hlt");
}
