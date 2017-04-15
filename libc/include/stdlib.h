#ifndef _STDLIB_H
#define _STDLIB_H 1

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

__attribute__((__noreturn__))
void abort(void);

/* Dynamic memory management */
void *calloc(size_t num, size_t size);
void *malloc(size_t size);
void free(void *ptr);

/* String conversion */
char *itoa(int value, char* str, int base);
char *utoa(unsigned int value, char* str, int base);
long strtol(const char *str, char **str_end, int base);

#ifdef __cplusplus
}
#endif

#endif
