#ifndef _KERNEL_INTERRUPTS_H
#define _KERNEL_INTERRUPTS_H

#include <stdint.h>

/* This defines what the stack looks like after an ISR was running */
typedef struct stack_t Stack;
struct stack_t
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

/*
 * IDT
 */

/* We are only using the first 32 entries here, but if any undefined IDT entry
   is hit, it will cause an "Unhandled Interrupt" exception */
#define NB_IDT_ENTRY 256

/* IDT entry

00-15: Offset
16-31: Selector
32-39: Unused
40-47: Flags (Type/Attributes)

   0-3: Gate type
   4: Storage segment
   5-6: Descriptor Privilege Level
   7: Present

48-63: Offset

*/

typedef struct idt_entry_t Idt_entry;
struct idt_entry_t {
   uint16_t offset_low;
   uint16_t selector;
   uint8_t unused;
   uint8_t flags;
   uint16_t offset_high;
} __attribute__((packed));

typedef struct idt_ptr_t Idt_ptr;
struct idt_ptr_t {
   uint16_t limit;
   uint32_t base;
} __attribute__((packed));


void idt_set_entry(uint8_t num, uint32_t base, uint16_t selector, uint8_t flags);
void idt_install(void);

/*
 * ISR
 */

#define NB_ISR_ROUTINES 256

void isr_install_handler(uint8_t isr, void (*handler)(Stack *registers));
void isr_uninstall_handler(uint8_t isr);
void isr_call_handler(Stack *registers);
void isr_install(void);

/*
 * IRQ
 */

#define NB_IRQ_ROUTINES 16

#define PIC1         0x20 /* master PIC */
#define PIC2         0xA0 /* slave PIC */
#define PIC1_CMD     PIC1
#define PIC1_DATA    (PIC1 + 1)
#define PIC2_CMD     PIC2
#define PIC2_DATA    (PIC2 + 1)
#define PIC1_OFFSET  0x20
#define PIC2_OFFSET  0x28

#define PIC_EOI 0x20

#define ICW1_ICW4 0x01
#define ICW1_INIT 0x10
#define ICW4_8086 0x01

void irq_install_handler(uint8_t irq, void (*handler)(Stack *registers));
void irq_uninstall_handler(uint8_t irq);
void irq_call_handler(Stack *registers);
void irq_install(void);

#endif
