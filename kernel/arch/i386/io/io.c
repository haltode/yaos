#include <stdint.h>

/* Sends a 8/16/32-bit value on a I/O location */
void outb(uint16_t port, uint8_t val)
{
   asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

/* Receives a 8/16/32-bit value from an I/O location */
uint8_t inb(uint16_t port)
{
   uint8_t val;
   asm volatile ( "inb %1, %0"
                  : "=a"(val)
                  : "Nd"(port) );
   return val;
}
