void sys_halt(void)
{
   asm volatile("hlt" ::: "memory");
}

void sys_enable_interrupts(void)
{
   asm volatile("sti" ::: "memory");
}

void sys_disable_interrupts(void)
{
   asm volatile("cli" ::: "memory");
}
