#include <stdbool.h>
#include <stdio.h>

#include <kernel/keyboard.h>
#include <kernel/shell.h>
#include <kernel/vfs.h>

Vfs_node *current_dir;

void shell_init(void)
{
   current_dir = vfs_get_root();

   unsigned char input_buffer[SHELL_BUFFER_SIZE + 1];
   size_t i;
   char c;
   while(true) {
      printf("user: %s> ", current_dir->name);

      i = 0;
      c = 0;
      while(i < SHELL_BUFFER_SIZE && (c = getchar()) != '\n') {
         /* Backspace */
         if(c == '\b') {
            if(i > 0) {
               putchar(c);
               --i;
            }
         }
         else {
            putchar(c);
            input_buffer[i] = c;
            ++i;
         }
      }

      putchar('\n');
      input_buffer[i] = '\0';
      keyboard_clear_buffer();

      shell_parse_input(input_buffer);
   }
}

void shell_parse_input(const unsigned char *input)
{
   printf("input: '%s'\n", input);
}

void shell_ls_command(void)
{

}

void shell_cd_command(const unsigned char *path)
{

}

void shell_cat_command(const unsigned char *path)
{

}

void shell_help_command(void)
{

}

void shell_exit_command(void)
{

}
