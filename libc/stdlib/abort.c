#include <stdio.h>
#include <stdlib.h>

__attribute__((__noreturn__))
void abort(void)
{
#ifdef __is_libk
   #include <kernel/sys.h>
   printf("kernel panic: abort()\n");
   sys_disable_interrupts();
   sys_halt();
#else
   /* TODO: Implement syscall */
   printf("abort()\n");
#endif
   while(1);
   __builtin_unreachable();
}
