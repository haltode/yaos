#ifndef _KERNEL_IO_H
#define _KERNEL_IO_H

#include <stdint.h>

/* Sends a 8/16/32-bit value on a I/O location */
inline void outb(uint32_t port, uint8_t val)
{
   asm volatile ("outb %%al,%%dx": :"d" (port), "a" (val));
   /* asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) ); */
}

/* Receives a 8/16/32-bit value from an I/O location */
inline uint8_t inb(uint32_t port)
{
   uint8_t val;
   asm volatile ("inb %%dx,%%al":"=a" (val):"d" (port));
   /* asm volatile ( "inb %1, %0" */
   /*                : "=a"(val) */
   /*                : "Nd"(port) ); */
   return val;
}

#endif
