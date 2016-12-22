#include <stdarg.h>
#include <stdio.h>

int printf(const char *format, ...)
{
   va_list arg;
   int written;

   va_start(arg, format);
   written = vprintf(format, arg);
   va_end(arg);

   return written;
}
