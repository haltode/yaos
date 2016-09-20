#include <stdint.h>

#include <kernel/isr.h>
#include <kernel/irq.h>

uint32_t timer_ticks = 0;

void timer_handler(struct stack *registers)
{
   /* The timer fires 18.222 times per second,
   18 ticks = approximately 1 second */

   ++timer_ticks;
}

/* Set up the system clock by installing the timer handler into IRQ0 */
void timer_install(void)
{
   irq_install_handler(0, timer_handler);
}
