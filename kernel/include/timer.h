#ifndef _KERNEL_TIMER_H
#define _KERNEL_TIMER_H

#define COMMAND_REG  0x43
#define DATA_REG1    0x40

void timer_wait(const uint32_t ticks);
void timer_install(void);

#endif
