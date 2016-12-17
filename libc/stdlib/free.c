#ifdef __is_libk

#include <kernel/doug_lea.h>

void kfree(void *ptr)
{
   DougLea_free(ptr);
}

#else

/* TODO: Implement system calls for free */

#endif
