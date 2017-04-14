#include <stddef.h>
#include <string.h>

char *strtok(char *str, const char *delimiters)
{
   /* On the first call, we expect a string as an argument, then each subsequent
      call starts right after the last token and we expect str to be a NULL
      pointer */
   static char *next_start;
   if(str != NULL)
      next_start = str;
   if(!*next_start)
      return NULL;

   /* The token only begins at the first non-delimiter character */
   while(*next_start && strchr(delimiters, *next_start) != NULL)
      ++next_start;
   if(!*next_start)
      return NULL;

   /* The token ends at the first delimiter character */
   size_t length = 0;
   while(*next_start && !strchr(delimiters, *next_start)) {
      ++next_start;
      ++length;
   }
   if(!*next_start)
      return NULL;

   /* Keep in memory the position of the token for other subsequent call, and
      return the beginning of the token found */
   char *token = next_start;
   ++next_start;
   *token = '\0';
   return token - length;
}
