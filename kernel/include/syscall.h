#ifndef _KERNEL_SYSCALL_H
#define _KERNEL_SYSCALL_H

#include <kernel/interrupts.h>

void syscall_init(void);
void syscall_handler(Stack *registers);

#endif
