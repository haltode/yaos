#ifndef _STDIO_H
#define _STDIO_H 1

#include <stdarg.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

int printf(const char *format, ...);
int putchar(int c);
int puts(const char *str);
int vprintf(const char *format, va_list arg);

#ifdef __cplusplus
}
#endif

#endif
