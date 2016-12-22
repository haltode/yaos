#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <kernel/io.h>
#include <kernel/vga.h>

#define VGA_CMD   0x3D4
#define VGA_DATA  0x3D5

static const uint8_t VGA_WIDTH = 80;
static const uint8_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t *) 0xB8000;

static uint8_t terminal_row;
static uint8_t terminal_column;
static uint8_t terminal_color;
static uint16_t *terminal_buffer;

static uint16_t terminal_pos(uint8_t x, uint8_t y)
{
   return y * VGA_WIDTH + x;
}

void terminal_init(void)
{
   terminal_row = 0;
   terminal_column = 0;
   terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
   terminal_buffer = VGA_MEMORY;

   for(size_t y = 0; y < VGA_HEIGHT; ++y) {
      for(size_t x = 0; x < VGA_WIDTH; ++x) {
         uint16_t index = terminal_pos(x, y);
         terminal_buffer[index] = vga_entry(0, terminal_color);
      }
   }
}

void terminal_set_color(uint8_t color)
{
   terminal_color = color;
}

static void terminal_movecursor(uint8_t x, uint8_t y)
{
   uint16_t index = terminal_pos(x, y);

   write_port(VGA_CMD, 0x0F);
   write_port(VGA_DATA, (uint8_t) index);
   write_port(VGA_CMD, 0x0E);
   write_port(VGA_DATA, (uint8_t) (index >> 8));
}

static void terminal_scrollup(uint8_t nb_rows)
{
   /* Shift each rows by nb_rows */
   for(size_t y = 0; y < VGA_HEIGHT; ++y) {
      uint8_t new_y = y + nb_rows;
      if(new_y < VGA_HEIGHT) {
         for(size_t x = 0; x < VGA_WIDTH; ++x) {
            uint16_t index = terminal_pos(x, y);
            uint16_t new_index = terminal_pos(x, new_y);
            terminal_buffer[index] = terminal_buffer[new_index];
         }
      }
      /* No more rows to shift so we use empty rows */
      else {
         for(size_t x = 0; x < VGA_WIDTH; ++x) {
            uint16_t index = terminal_pos(x, y);
            terminal_buffer[index] = vga_entry(0, terminal_color);
         }
      }
   }

   /* Update cursor */
   if(nb_rows > terminal_row)
      terminal_row = 0;
   else
      terminal_row -= nb_rows;
   terminal_movecursor(terminal_column, terminal_row);
}

static void terminal_newline(void)
{
   terminal_column = 0;
   ++terminal_row;
   if(terminal_row == VGA_HEIGHT)
      terminal_scrollup(1);
}

static void terminal_backspace(void)
{
   if(terminal_column == 0) {
      terminal_column = VGA_WIDTH - 1;
      if(terminal_row == 0)
         terminal_column = 0;
      else
         --terminal_row;

      /* Go to the last character on the line */
      uint16_t empty = vga_entry(0, terminal_color);
      uint16_t index = terminal_pos(terminal_column, terminal_row);
      while(terminal_column > 0 && terminal_buffer[index] == empty) {
         --terminal_column;
         index = terminal_pos(terminal_column, terminal_row);
      }
      /* Don't erase the last character immediately */
      if(terminal_buffer[index] != empty && terminal_column + 1 < VGA_WIDTH)
         ++terminal_column;
   }
   else
      --terminal_column;

   uint16_t index = terminal_pos(terminal_column, terminal_row);
   terminal_buffer[index] = vga_entry(0, terminal_color);
}

static void terminal_putentryat(unsigned char c, uint8_t x, uint8_t y)
{
   uint16_t index = terminal_pos(x, y);
   terminal_buffer[index] = vga_entry(c, terminal_color);
}

void terminal_putchar(char c)
{
   unsigned char uc = c;

   /* Newline */
   if(uc == '\n')
      terminal_newline();
   /* Backspace */
   else if(uc == '\b')
      terminal_backspace();
   /* Other character */
   else {
      terminal_putentryat(uc, terminal_column, terminal_row);
      ++terminal_column;
      if(terminal_column == VGA_WIDTH)
         terminal_newline();
   }

   terminal_movecursor(terminal_column, terminal_row);
}

void terminal_write(const char *data, size_t length)
{
   for(size_t i = 0; i < length; ++i)
      terminal_putchar(data[i]);
}

void terminal_writestring(const char *data)
{
   terminal_write(data, strlen(data));
}
