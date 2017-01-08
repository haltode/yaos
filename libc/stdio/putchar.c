int putchar(int c)
{
   char data = (char) c;

#ifdef __is_libk
   #include <kernel/tty.h>
   terminal_write(&data, sizeof(data));
#else
   #include <sys.h>
   syscall(PUTCHAR_SYSCALL, (int) &data, (int) sizeof(data), 0);
#endif

   return c;
}
