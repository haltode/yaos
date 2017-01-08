#include <stdio.h>

#include <kernel/syscall.h>

void test_syscall(void)
{
   int ret;
   int function = 0;
   int p1 = (int) ("test syscall\n");

   asm volatile("int $0x80" : "=a" (ret) : "0" (function), "b" (p1));
   printf("ret: 0x%x\n", ret);
}
