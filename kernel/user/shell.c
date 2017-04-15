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

   if(strcmp(command, "ls") == 0)
      shell_ls_command();
   else if(strcmp(command, "cd") == 0)
      shell_cd_command(first_param);
   else if(strcmp(command, "cat") == 0)
      shell_cat_command(first_param);
   else if(strcmp(command, "help") == 0)
      shell_help_command();
   else if(strcmp(command, "exit") == 0)
      shell_exit_command();
   else {
      printf("Unknown command: '%s'\n", command);
      printf("Type 'help' to print out the list of commands.\n");
   }
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
   puts("List of available commands:");
   puts("ls - list directory contents");
   puts("cd [directory] - change the working directory");
   puts("cat [file] - print out file content");
   puts("help - print out this help menu");
   puts("exit - cause the shell to exit");
}

void shell_exit_command(void)
{

}
