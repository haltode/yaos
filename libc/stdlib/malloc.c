#include <stddef.h>

#ifdef __is_libk

#include <kernel/doug_lea.h>

void *kmalloc(size_t size)
{
   return DougLea_malloc(size);
}

#else

/* TODO: Syscall */

#endif
