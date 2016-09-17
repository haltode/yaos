#ifndef ARCH_I386_ISR_H
#define ARCH_I386_ISR_H

/* This defines what the stack looks like after an ISR was running */
struct stack
{
   /* Pushed the segs last */
   uint32_t gs, fs, es, ds;
   /* Pushed by 'pusha' */
   uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
   /* Our 'push #' and ecodes do this */
   uint32_t id, err_code;
   /* Pushed by the processor automatically */ 
   uint32_t eip, cs, eflags, useresp, ss;
};

#endif
