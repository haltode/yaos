#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool print(char *data, size_t length)
{
   unsigned char *bytes = (unsigned char *) data;
   for(size_t i = 0; i < length; ++i)
      if(putchar(bytes[i]) == EOF)
         return false;
   return true;
}

static bool is_specifier(char c)
{
   static const char *specifiers = "dxcs%";
   size_t spec_len = strlen(specifiers);

   for(size_t i = 0; i < spec_len; ++i)
      if(c == specifiers[i])
         return true;
   return false;
}

int vprintf(const char *format, va_list arg)
{
   int written;
   written = 0;

   for(size_t i = 0; format[i] != '\0'; ++i) {
      /* Specifiers */
      if(format[i] == '%') {
         ++i;

         /* Skip everything useless after the % (spaces, tab, etc.) */
         while(format[i] != '\0' && !is_specifier(format[i])) {
            /* Unknown specifier */
            if(isalpha(format[i]))
               return -1;
            ++i;
         }
         /* Check if we have a specifier or not */
         if(format[i] == '\0')
            return -1;

         /* int (decimal) ) */
         if(format[i] == 'd') {
            int number = va_arg(arg, int);
            char str[16];
            size_t len;

            itoa(number, str, 10);
            len = strlen(str);
            if(!print(str, len))
               return -1;
            written += len;
         }
         /* int (hexadecimal) */
         if(format[i] == 'x') {
            unsigned int number = va_arg(arg, unsigned int);
            char str[16];
            size_t len;

            utoa(number, str, 16);
            len = strlen(str);
            if(!print(str, len))
               return -1;
            written += len;
         }
         /* char */
         else if(format[i] == 'c') {
            /* char promotes to int */
            char c = (char) va_arg(arg, int);
            if(!print(&c, sizeof(c)))
               return -1;
            ++written;
         }
         /* string */
         else if(format[i] == 's') {
            char *str = va_arg(arg, char*);
            size_t len = strlen(str);
            if(!print(str, len))
               return -1;
            written += len;
         }
         /* '%' */
         else if(format[i] == '%') {
            char c = '%';
            if(!print(&c, sizeof(c)))
               return -1;
            ++written;
         }
      }
      /* Normal character (letter, escape sequence, etc.) */
      else {
         char c = format[i];
         if(!print(&c, sizeof(c))) 
            return -1;
         ++written;
      }
   }
   
   return written;
}
