#include <stdio.h>

#if defined(__is_libk)
#include <kernel/tty.h>
#endif

int putchar(int ic)
{
#if defined(__is_libk)
   char c = (char) ic;

   /* Escape sequence (newline) */
   if(c == '\n')
      terminal_newline();
   /* Other character */
   else
      terminal_write(&c, sizeof(c));
#else
   /* TODO: Implement stdio and the write system call. */
#endif
   return ic;
}
