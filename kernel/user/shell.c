#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <kernel/keyboard.h>
#include <kernel/shell.h>
#include <kernel/vfs.h>

Vfs_node *current_dir;

void shell_init(void)
{
   current_dir = vfs_get_root();

   char input_buffer[SHELL_BUFFER_SIZE + 1];
   size_t i;
   char c;
   while(true) {
      printf("user: %s> ", current_dir->name);

      i = 0;
      c = 0;
      while(i < SHELL_BUFFER_SIZE) {
         c = getchar();

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
            /* Newline */
            if(c == '\n')
               break;
         }
      }

      input_buffer[i] = '\0';
      keyboard_clear_buffer();

      shell_parse_input(input_buffer);
   }
}

void shell_parse_input(char *input)
{
   char *command = strtok(input, " \n");
   char *first_param = strtok(NULL, " \n");
   if(command)
      printf("command: '%s'\n", command);
   if(first_param)
      printf("first_param: '%s'\n", first_param);
}

void shell_ls_command(void)
{

}

void shell_cd_command(char *path)
{

}

void shell_cat_command(char *path)
{

}

void shell_help_command(void)
{

}

void shell_exit_command(void)
{

}
