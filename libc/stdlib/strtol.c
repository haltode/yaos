#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>

/* Convert a number as a string in a certain base to an integer value */
long strtol(const char *str, char **str_end, int base)
{
   /* Unused parameter (avoid a warning) */
   (void)(str_end);

   long value = 0;
   bool is_negative = false;
   size_t i = 0;

   /* Skip white space */
   while(isspace(str[i]))
      ++i;

   /* Pick up the leading sign */
   if(str[i] == '-') {
      is_negative = true;
      ++i;
   }
   else if(str[i] == '+')
      ++i;

   /* Base specific ('0x' and '0X' for hexadecimal and '0' for octal) */
   if(   (base == 0 || base == 16) && 
         str[i] == '0' && (str[i + 1] == 'x' || str[i + 1] == 'X')) {
      i += 2;
      base = 16;
   }
   if(base == 0) {
      if(str[i] == '0')
         base = 8;
      else
         base = 10;
   }

   while(true) {
      int current = str[i];

      if(isdigit(current))
         current -= '0';
      else if(isupper(current))
         current -= 'A' - 10;
      else if(islower(current))
         current -= 'a' - 10;
      else
         break;

      if(current >= base)
         break;

      value *= base;
      value += current;

      ++i;
   }

   if(is_negative)
      value = -value;

   return value;
}
