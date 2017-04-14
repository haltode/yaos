#ifndef _STRING_H
#define _STRING_H 1

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int memcmp(const void *ptr1, const void *ptr2, size_t size);
void *memcpy(void *destination, const void *source, size_t size);
void *memmove(void *destination, const void *source, size_t size);
void *memset(void *ptr, int value, size_t size);

char *strcpy(char *dest, const char *src);
char *strstr(const char *str1, const char *str2);
char *strchr(const char *str, int character);
char *strtok(char *str, const char *delimiters);
int strcmp(const char *str1, const char *str2);
size_t strlen(const char *str);

#ifdef __cplusplus
}
#endif

#endif
