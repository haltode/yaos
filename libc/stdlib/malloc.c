#include <stddef.h>

#ifdef __is_libk

#include <kernel/doug_lea.h>

void *kmalloc(size_t size)
{
   return DougLea_malloc(size);
}

#else

#include <sys.h>

void *malloc(size_t size)
{
   return syscall(MALLOC_SYSCALL, (int) size, 0, 0);
}

#endif
