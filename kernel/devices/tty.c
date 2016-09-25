#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/tty.h>
#include <kernel/vga.h>
#include <kernel/io.h>

#define VGA_CMD   0x3D4
#define VGA_DATA  0x3D5

static const uint8_t VGA_WIDTH = 80;
static const uint8_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

static uint8_t terminal_row;
static uint8_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

void terminal_initialize(void)
{
   terminal_row = 0;
   terminal_column = 0;
   terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
   terminal_buffer = VGA_MEMORY;

   for(size_t y = 0; y < VGA_HEIGHT; ++y) {
      for(size_t x = 0; x < VGA_WIDTH; ++x) {
         const uint16_t index = y * VGA_WIDTH + x;
         terminal_buffer[index] = vga_entry(' ', terminal_color);
      }
   }
}

static void terminal_setcolor(uint8_t color)
{
   terminal_color = color;
}

static void terminal_movecursor(uint8_t x, uint8_t y)
{
   const uint16_t index = y * VGA_WIDTH + x;

   write_port(VGA_CMD, 0x0F);
   write_port(VGA_DATA, (uint8_t) index);
   write_port(VGA_CMD, 0x0E);
   write_port(VGA_DATA, (uint8_t) (index >> 8));
}

static void terminal_newline(void)
{
   terminal_column = 0;
   ++terminal_row;
   if(terminal_row == VGA_HEIGHT) {
      /* TODO: implement scrolling/clearing the screen */
      terminal_row = 0;
   }
}

void terminal_putentryat(unsigned char c, uint8_t color, uint8_t x, uint8_t y)
{
   const uint16_t index = y * VGA_WIDTH + x;
   terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c)
{
   unsigned char uc = c;

   /* Escape sequence (newline) */
   if(c == '\n')
      terminal_newline();
   /* Other character */
   else {
      terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
      ++terminal_column;
      if(terminal_column == VGA_WIDTH)
         terminal_newline();
   }

   terminal_movecursor(terminal_column, terminal_row);
}

void terminal_write(const char* data, size_t length)
{
   for(size_t i = 0; i < length; ++i)
      terminal_putchar(data[i]);
}

void terminal_writestring(const char* data)
{
   terminal_write(data, strlen(data));
}
