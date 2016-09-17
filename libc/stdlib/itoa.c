#include <string.h>
#include <stdbool.h>

static void reverse(char* str, size_t length)
{
   size_t start, end;
   char tmp;
   start = 0;
   end = length - 1;

   while(start < end) {
      tmp = str[start];
      str[start] = str[end];
      str[end] = tmp;

      ++start;
      --end;
   }
}

char* itoa(int value, char* str, int base)
{
   bool is_negative = false;
   size_t i = 0;

   /* Handle the special case */
   if(value == 0) {
      str[i] = '0';
      str[i + 1] = '\0';
      return str;
   }

   /* Only base 10 numbers are considered signed */
   if(base == 10 && value < 0) {
      is_negative = true;
      value = -value;
   }

   while(value != 0) {
      int remainder = value % base;
      value /= base;
      /* For bigger bases than 10 (eg: hexadecimal) */
      if(remainder > 9)
         str[i] = (remainder - 10) + 'a';
      else
         str[i] = remainder + '0';
      ++i;
   }

   if(is_negative) {
      str[i] = '-';
      ++i;
   }

   str[i] = '\0';

   /* The converted string is reversed (because of the method we are using) */
   reverse(str, i);
   return str;
}
