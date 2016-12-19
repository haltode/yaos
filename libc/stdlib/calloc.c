#include <stddef.h>

#ifdef __is_libk

#include <kernel/doug_lea.h>

void *kcalloc(size_t num, size_t size)
{
   return DougLea_calloc(num, size);
}

#else

/* TODO: Implement system calls for calloc */

#endif
