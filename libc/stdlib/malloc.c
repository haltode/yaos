#include <stddef.h>

void *malloc(size_t size)
{

#ifdef __is_libk
   #include <kernel/doug_lea.h>
   return DougLea_malloc(size);
#else
   #include <sys.h>
   return syscall(MALLOC_SYSCALL, (int) size, 0, 0);
#endif

}
