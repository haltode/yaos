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

#endif
