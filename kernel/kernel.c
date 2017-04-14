#include <stdio.h>

#include <kernel/gdt.h>
#include <kernel/interrupts.h>
#include <kernel/keyboard.h>
#include <kernel/log.h>
#include <kernel/memory.h>
#include <kernel/multiboot.h>
#include <kernel/shell.h>
#include <kernel/sys.h>
#include <kernel/syscall.h>
#include <kernel/timer.h>
#include <kernel/tty.h>
#include <kernel/user_space.h>
#include <kernel/vfs.h>

Multiboot_info *boot_info;

void kernel_main(Multiboot_info *args)
{
   boot_info = args;

   terminal_init();
   kernel_log(INFO_MSG, "TTY loaded");

   gdt_install();
   kernel_log(INFO_MSG, "GDT loaded");

   idt_install();
   kernel_log(INFO_MSG, "IDT loaded");
   isr_install();
   kernel_log(INFO_MSG, "ISR loaded");
   irq_install();
   kernel_log(INFO_MSG, "IRQ loaded");

   phys_mem_init();
   kernel_log(INFO_MSG, "Physical memory manager enabled");
   virt_mem_init();
   kernel_log(INFO_MSG, "Virtual memory manager enabled");
   heap_init();
   kernel_log(INFO_MSG, "Heap manager enabled");

   timer_install();
   kernel_log(INFO_MSG, "Timer enabled");

   keyboard_install();
   kernel_log(INFO_MSG, "Keyboard enabled");

   vfs_init();
   kernel_log(INFO_MSG, "Virtual file system initialized");
   
   puts("");
   puts("Hello kernel world!");

   syscall_init();
   enter_user_space();

   puts("");
   puts("Hello user world!");

   shell_init();
}
