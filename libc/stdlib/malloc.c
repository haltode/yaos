#include <stddef.h>

#ifdef __is_libk

void *kmalloc(size_t size)
{
   return NULL;
}

#else

/* TODO: Implement system calls for malloc */

#endif
