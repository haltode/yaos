#include <stddef.h>

char *strchr(const char *str, int character)
{
   size_t i = 0;
   while(str[i] != (char) character) {
      if(str[i] == '\0')
         return NULL;
      ++i;
   }

   return (char *)(str + i);
}
