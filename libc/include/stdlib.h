#ifndef _STDLIB_H
#define _STDLIB_H 1

#include <stddef.h>

#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

__attribute__((__noreturn__))
void abort(void);

char *itoa(int value, char* str, int base);
char *utoa(unsigned int value, char* str, int base);
long strtol(const char *str, char **str_end, int base);

void *kcalloc(size_t num, size_t size);
void *kmalloc(size_t size);
void kfree(void *ptr);

#ifdef __cplusplus
}
#endif

#endif
