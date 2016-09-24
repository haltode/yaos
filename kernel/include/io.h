#ifndef _KERNEL_IO_H
#define _KERNEL_IO_H

#include <stdint.h>

/* Sends a 8/16/32-bit value on a I/O location */
inline void write_port(uint32_t port, uint8_t val)
{
   asm volatile ("outb %%al,%%dx": :"d" (port), "a" (val));
}

/* Receives a 8/16/32-bit value from an I/O location */
inline uint8_t read_port(uint32_t port)
{
   uint8_t val;
   asm volatile ("inb %%dx,%%al":"=a" (val):"d" (port));
   return val;
}

inline void io_wait(void)
{
   /* TODO: This is probably fragile. */
   asm volatile ( "jmp 1f\n\t"
                  "1:jmp 2f\n\t"
                  "2:" );
}

#endif
