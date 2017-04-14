int getchar(void)
{

#ifdef __is_libk
   #include <kernel/keyboard.h>
   return keyboard_getchar();
#else
   #include <sys.h>
   return syscall(GETCHAR_SYSCALL, 0, 0, 0);
#endif

}
