#include <stdio.h>
#include <stdlib.h>

#include <kernel/memory.h>
#include <kernel/test.h>

void test_heap(void)
{
   int *ret = kmalloc(8);
   printf("ret: 0x%x\n", ret);
   printf("*ret: 0x%x\n", *ret);
   printf("&ret: 0x%x\n", &ret);

   int *ret2 = kmalloc(8);
   printf("ret2: 0x%x\n", ret2);
   printf("*ret2: 0x%x\n", *ret2);
   printf("&ret2: 0x%x\n", &ret2);

   kfree(ret);
   printf("ret: 0x%x\n", ret);
   printf("*ret: 0x%x\n", *ret);
   printf("&ret: 0x%x\n", &ret);

   int *ret3 = kmalloc(8);
   printf("ret3: 0x%x\n", ret3);
   printf("*ret3: 0x%x\n", *ret3);
   printf("&ret3: 0x%x\n", &ret3);

   kfree(ret2);
   kfree(ret3);
}
