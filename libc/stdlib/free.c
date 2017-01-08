#ifdef __is_libk

#include <kernel/doug_lea.h>

void kfree(void *ptr)
{
   DougLea_free(ptr);
}

#else

#include <sys.h>

void free(void *ptr)
{
   syscall(FREE_SYSCALL, (int) ptr, 0, 0);
}

#endif
