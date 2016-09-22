#ifndef _KERNEL_TIMER_H
#define _KERNEL_TIMER_H

void timer_wait(const uint32_t ticks);
void timer_install(void);

#endif
