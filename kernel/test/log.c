#include <kernel/log.h>

void test_log(void)
{
   int x = 42;
   char *str = "test";

   kernel_log(INFO_MSG, "This is an info: %d", x);
   kernel_log(WARNING_MSG, "This is a warning: 0x%x", x);
   kernel_log(ERROR_MSG, "This is an error: %s", str);
}
