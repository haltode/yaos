#ifndef _KERNEL_IO_H
#define _KERNEL_IO_H

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);

#endif
