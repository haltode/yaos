#include <stdint.h>
#include <stdio.h>

#include <kernel/interrupts.h>
#include <kernel/syscall.h>

#define NB_SYSCALL 1

void *syscalls[NB_SYSCALL] = {
   printf 
};

void syscall_init(void)
{
   isr_install_handler(0x80, syscall_handler);
}

void syscall_handler(Stack *registers)
{
   int sys_index = registers->eax;

   if(sys_index >= NB_SYSCALL)
      return;
   void *function = syscalls[sys_index];

   int ret;
   asm volatile ("   push %1; \
                     push %2;   \
                     push %3;   \
                     push %4;   \
                     push %5;   \
                     call *%6;  \
                     pop %%ebx; \
                     pop %%ebx; \
                     pop %%ebx; \
                     pop %%ebx; \
                     pop %%ebx; \
         " : "=a" (ret) : "r" (registers->edi), "r" (registers->esi), "r" (registers->edx), "r" (registers->ecx), "r" (registers->ebx), "r" (function));
   registers->eax = ret;
}
