#include <stdint.h>

#include <kernel/interrupts.h>
#include <kernel/io.h>

#define COMMAND_REG 0x43
#define DATA_REG1 0x40

/* We need to use the 'volatile' keyword to stop
   the compiler from optimizing the variable */
volatile uint32_t timer_ticks = 0;

void timer_wait(const uint32_t ticks)
{
   uint32_t total_ticks = timer_ticks + ticks;
   while(timer_ticks < total_ticks);
}

void timer_handler(struct stack *registers)
{
   ++timer_ticks;
}

void timer_phase(const uint32_t hz)
{
   uint32_t divisor = 1193180 / hz;

   write_port(COMMAND_REG, 0x36);
   /* Set the low byte of 'divisor' */
   write_port(DATA_REG1, divisor & 0xFF);
   /* Set the high byte of 'divisor' */
   write_port(DATA_REG1, divisor >> 8);
}

void timer_install(void)
{
   /* Set up the system clock by installing the timer handler into IRQ0 */
   irq_install_handler(0, timer_handler);

   /* 100Hz */
   timer_phase(100);
}
