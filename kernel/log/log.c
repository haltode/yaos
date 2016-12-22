#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <kernel/log.h>
#include <kernel/tty.h>
#include <kernel/vga.h>

void kernel_log(Message type, const char *format, ...)
{
   va_list arg;

   va_start(arg, format);

   switch(type) {
      case INFO_MSG:
         printf("(kernel info) ");
         vprintf(format, arg);
         puts("");
         break;
      case WARNING_MSG:
         terminal_set_color(vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK));
         printf("(kernel warning) ");
         vprintf(format, arg);
         puts("");
         terminal_set_color(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
         break;
      case ERROR_MSG:
         terminal_set_color(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_RED));
         printf("(kernel error) ");
         vprintf(format, arg);
         puts("");
         terminal_set_color(vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK));
         break;
      default:
         kernel_log(ERROR_MSG, "Unknown message type in kernel_log: '%d'", type);
         break;
   }

   va_end(arg);
}
