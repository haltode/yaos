#include <stdio.h>

#include <kernel/gdt.h>
#include <kernel/interrupts.h>
#include <kernel/keyboard.h>
#include <kernel/memory.h>
#include <kernel/multiboot.h>
#include <kernel/timer.h>
#include <kernel/tty.h>

void kernel_main(Multiboot_info *boot_info)
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

   /* int ret = virt_mem_alloc_page(0x400000); */
   /* printf("%d\n", ret); */

   #include <stdlib.h>
   int *ret = kmalloc(8);
   printf("ret: 0x%x\n", ret);
   printf("*ret: 0x%x\n", *ret);
   printf("&ret: 0x%x\n", &ret);

   int *ret2 = kmalloc(8);
   printf("ret2: 0x%x\n", ret2);
   printf("*ret2: 0x%x\n", *ret2);
   printf("&ret2: 0x%x\n", &ret2);

   kfree(ret);
   printf("ret: 0x%x\n", ret);
   printf("*ret: 0x%x\n", *ret);
   printf("&ret: 0x%x\n", &ret);

   /* extern Node *free_space; */
   /* printf("0x%x\n", free_space); */
   /* printf("0x%x\n", free_space->size); */
   /* printf("0x%x\n", free_space->next); */
   /* printf("0x%x\n", free_space->prev); */
   /* int *ret3 = kmalloc(8); */
   /* printf("ret3: 0x%x\n", ret3); */
   /* printf("*ret3: 0x%x\n", *ret3); */
   /* printf("&ret3: 0x%x\n", &ret3); */

   /* Make sure the main function doesn't exit prematurely 
      (Otherwise it disables interrupts) */
   for(;;)
      asm("hlt");
}
