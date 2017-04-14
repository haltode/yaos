#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include <kernel/doug_lea.h>
#include <kernel/interrupts.h>
#include <kernel/keyboard.h>
#include <kernel/sys.h>
#include <kernel/syscall.h>
#include <kernel/tty.h>

#define NB_SYSCALL 6

void *syscalls[NB_SYSCALL] = {
   terminal_write,
   keyboard_getchar,

   DougLea_malloc,
   DougLea_free,
   DougLea_calloc,

   sys_halt
};

void syscall_handler(Stack *registers)
{
   int sys_index = registers->eax;
   assert(sys_index < NB_SYSCALL);

   void *function = syscalls[sys_index];

   int ret;
   asm volatile ("   push %1;   \
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
                     " : "=a" (ret) : 
                     "r" (registers->edi), "r" (registers->esi),
                     "r" (registers->edx), "r" (registers->ecx), 
                     "r" (registers->ebx), "r" (function));
   registers->eax = ret;
}

void syscall_init(void)
{
   isr_install_handler(128, syscall_handler);
}
