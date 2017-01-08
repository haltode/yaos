__attribute__((__noreturn__))
void abort(void)
{
#ifdef __is_libk
   #include <kernel/log.h>
   #include <kernel/sys.h>

   kernel_log(ERROR_MSG, "Kernel panic");
   sys_disable_interrupts();
   sys_halt();
#else
   #include <sys.h>
   syscall(ABORT_SYSCALL, 0, 0, 0);
#endif

   while(1);
   __builtin_unreachable();
}
