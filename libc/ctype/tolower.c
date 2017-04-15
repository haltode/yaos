#include <ctype.h>

int tolower(int c)
{
   if(isupper(c))
      return c + ('a' - 'A');
   else
      return c;
}
