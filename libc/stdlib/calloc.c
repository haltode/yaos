#include <stddef.h>

void *calloc(size_t num, size_t size)
{

#ifdef __is_libk
   #include <kernel/doug_lea.h>
   return DougLea_calloc(num, size);
#else
   #include <sys.h>
   return syscall(CALLOC_SYSCALL, (int) num, (int) size, 0);
#endif

}
