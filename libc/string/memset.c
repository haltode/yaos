#include <stddef.h>

void *memset(void *ptr, int value, size_t size)
{
   unsigned char *buf = (unsigned char *) ptr;

   for(size_t i = 0; i < size; ++i)
      buf[i] = (unsigned char) value;

   return ptr;
}
