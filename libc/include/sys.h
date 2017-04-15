#ifndef _SYS_H
#define _SYS_H 1

enum syscall_t {
   PUTCHAR_SYSCALL,
   GETCHAR_SYSCALL,

   MALLOC_SYSCALL,
   FREE_SYSCALL,
   CALLOC_SYSCALL,

   OPEN_SYSCALL,
   CLOSE_SYSCALL,
   READ_SYSCALL,
   WRITE_SYSCALL,
   READ_DIR_SYSCALL,
   FIND_DIR_SYSCALL,

   ABORT_SYSCALL
};

#ifdef __cplusplus
extern "C" {
#endif

int syscall(int function, int param1, int param2, int param3);

#ifdef __cplusplus
}
#endif

#endif
