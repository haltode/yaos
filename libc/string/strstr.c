#include <stddef.h>
#include <string.h>

char *strstr(const char *str1, const char *str2)
{
   size_t len_str1 = strlen(str1);
   size_t len_str2 = strlen(str2);
   size_t i, j;

   for(i = 0; i < len_str1; ++i) {
      for(j = 0; j < len_str2; ++j) {
         if(i + j >= len_str1 || str1[i + j] != str2[j])
            break;
      }

      if(j == len_str2)
         return (char *)(str1 + i);
   }

   return NULL;
}
