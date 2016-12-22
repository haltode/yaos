#include <stddef.h>

void *memcpy(void *destination, const void *source, size_t size)
{
   unsigned char *dst = (unsigned char *) destination;
   const unsigned char *src = (const unsigned char *) source;

   for(size_t i = 0; i < size; ++i)
      dst[i] = src[i];

   return destination;
}
