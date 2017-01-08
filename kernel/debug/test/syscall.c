#include <stdio.h>

#include <kernel/syscall.h>

void test_syscall(void)
{
   char c = 'a';
   int ret;

   /* terminal_write syscall */
   int function = 0;
   int p1 = (int) &c;
   int p2 = (int) sizeof(c);

   asm volatile("int $0x80" : "=a" (ret) : "0" (function), "b" (p1), "c" (p2));
   puts("");
   printf("ret: 0x%x\n", ret);
}
