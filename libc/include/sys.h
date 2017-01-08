#ifndef _SYS_H
#define _SYS_H 1

#define PUTCHAR_SYSCALL    0

#define MALLOC_SYSCALL     1
#define FREE_SYSCALL       2
#define CALLOC_SYSCALL     3

#define ABORT_SYSCALL      4

#ifdef __cplusplus
extern "C" {
#endif

int syscall(int function, int param1, int param2, int param3);

#ifdef __cplusplus
}
#endif

#endif
