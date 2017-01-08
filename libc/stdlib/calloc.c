#include <stddef.h>

#ifdef __is_libk

#include <kernel/doug_lea.h>

void *kcalloc(size_t num, size_t size)
{
   return DougLea_calloc(num, size);
}

#else

#include <sys.h>

void *calloc(size_t num, size_t size)
{
   return syscall(CALLOC_SYSCALL, (int) num, (int) size, 0);
}

#endif
