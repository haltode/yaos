#ifndef _KERNEL_KEYBOARD_H
#define _KERNEL_KEYBOARD_H

#define KEYBOARD_DATA 0x60

#define LSHIFT 0x29
#define RSHIFT 0x35
#define CTRL   0x1C
#define ALT    0x37

void keyboard_install(void);

#endif
