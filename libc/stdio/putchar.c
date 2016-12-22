int putchar(int c)
{
#ifdef __is_libk
   #include <kernel/tty.h>
   char data = (char) c;
   terminal_write(&data, sizeof(data));
#else
   /* TODO: Syscall */
#endif

   return c;
}
