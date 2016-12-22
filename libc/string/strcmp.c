#include <stddef.h>

int strcmp(const char *str1, const char *str2)
{
   size_t i = 0;

   while(str1[i] != '\0' && str1[i] == str2[i])
      ++i;

   return str1[i] - str2[i];
}
