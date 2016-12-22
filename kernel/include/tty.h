#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>
#include <stdint.h>

void terminal_init(void);
void terminal_set_color(uint8_t color);
void terminal_putchar(char c);
void terminal_write(const char *data, size_t length);
void terminal_writestring(const char *data);

#endif
