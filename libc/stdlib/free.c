void free(void *ptr)
{

#ifdef __is_libk
   #include <kernel/doug_lea.h>
   DougLea_free(ptr);
#else
   #include <sys.h>
   syscall(FREE_SYSCALL, (int) ptr, 0, 0);
#endif

}
