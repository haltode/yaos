#include <stdio.h>

__attribute__((__noreturn__))
void abort(void)
{
#ifdef __is_libk
   #include <kernel/sys.h>
   printf("kernel panic: abort()\n");
   sys_disable_interrupts();
   sys_halt();
#else
   /* TODO: Syscall */
#endif

   while(1);
   __builtin_unreachable();
}
