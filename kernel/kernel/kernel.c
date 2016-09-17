#include <stdio.h>

#include <kernel/gdt.h>
#include <kernel/tty.h>

void kernel_main(void)
{
   gdt_install();
   terminal_initialize();
   printf("Hello, kernel World!\n");
}
