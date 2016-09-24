#include <stdio.h>
#include <stdint.h>

#include <kernel/interrupts.h>
#include <kernel/io.h>

#define KEYBOARD_DATA 0x60

/* Basic US keyboard layout */
unsigned char us_layout[128] = {
   0, 27,
   '1','2','3','4','5','6','7','8','9','0',
   '-','=','\b',
   '\t', /* tab */
   'q','w','e','r','t','y','u','i','o','p','[',']','\n',
   0, /* control */
   'a','s','d','f','g','h','j','k','l',';','\'', '`',
   0, /* left shift */
   '\\','z','x','c','v','b','n','m',',','.','/',
   0, /* right shift */
   '*',
   0, /* alt */
   ' ', /* space */
   0, /* caps lock */
   0, /* F1 [59] */
   0, 0, 0, 0, 0, 0, 0, 0,
   0, /* ... F10 */
   0, /* 69 num lock */
   0, /* scroll lock */
   0, /* home */
   0, /* up */
   0, /* page up */
   '-',
   0, /* left arrow */
   0,
   0, /* right arrow */
   '+',
   0, /* 79 end */
   0, /* down */
   0, /* page down */
   0, /* insert */
   0, /* delete */
   0, 0, 0,
   0, /* F11 */
   0, /* F12 */
   0, /* everything else */
};

void keyboard_handler(struct stack *registers)
{
   uint8_t scancode;

   scancode = read_port(KEYBOARD_DATA);

   /* If the top bit of the byte we read from the keyboard is
      set, that means that a key has just been released */
   if(scancode & 0x80) {
   }
   /* Normal key press */
   else
      putchar(us_layout[scancode]);
}

void keyboard_install(void)
{
   /* Set up the keyboard by installing it's handler into IRQ1 */
   irq_install_handler(1, keyboard_handler);
}
