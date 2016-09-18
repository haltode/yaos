#ifndef _KERNEL_IRQ_H
#define _KERNEL_IRQ_H

#include <stdint.h>

#include <kernel/isr.h>

void irq_install_handler(uint8_t irq, void (*handler)(struct stack *registers));
void irq_uninstall_handler(uint8_t irq);
void irq_install(void);

#endif
