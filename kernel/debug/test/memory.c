#include <stdio.h>
#include <stdlib.h>

#include <kernel/doug_lea.h>
#include <kernel/memory.h>

void test_phys_mem(void)
{
   int *ret = phys_mem_alloc_frame();
   printf("(alloc) ret: 0x%x\n", ret);

   int *ret1 = phys_mem_alloc_frame();
   printf("(alloc) ret1: 0x%x\n", ret1);
   
   phys_mem_free_frame(ret);
   printf("(free) ret: 0x%x\n", ret);

   int *ret2 = phys_mem_alloc_frame();
   printf("(alloc) ret2: 0x%x\n", ret2);

   int *ret3 = phys_mem_alloc_frame();
   printf("(alloc) ret3: 0x%x\n", ret3);

   phys_mem_free_frame(ret1);
   printf("(free) ret1: 0x%x\n", ret1);
   phys_mem_free_frame(ret2);
   printf("(free) ret2: 0x%x\n", ret2);
   phys_mem_free_frame(ret3);
   printf("(free) ret3: 0x%x\n", ret3);
}

void test_heap(void)
{
   int *ret = malloc(8);
   printf("ret: 0x%x\n", ret);
   printf("*ret: 0x%x\n", *ret);
   printf("&ret: 0x%x\n", &ret);

   int *ret2 = malloc(8);
   printf("ret2: 0x%x\n", ret2);
   printf("*ret2: 0x%x\n", *ret2);
   printf("&ret2: 0x%x\n", &ret2);

   free(ret);
   printf("ret: 0x%x\n", ret);
   printf("*ret: 0x%x\n", *ret);
   printf("&ret: 0x%x\n", &ret);

   int *ret3 = malloc(8);
   printf("ret3: 0x%x\n", ret3);
   printf("*ret3: 0x%x\n", *ret3);
   printf("&ret3: 0x%x\n", &ret3);

   free(ret2);
   free(ret3);
}

void test_doug_lea(void)
{
   extern uint32_t *kernel_heap_top;

   int *ret = DougLea_malloc(8);
   printf("malloc\n");
   printf("ret: 0x%x *ret: 0x%x &ret: 0x%x\n", ret, *ret, &ret);
   printf("kernel_heap_top: 0x%x\n", kernel_heap_top);

   int *ret2 = DougLea_malloc(1024);
   printf("malloc\n");
   printf("ret2: 0x%x *ret2: 0x%x &ret2: 0x%x\n", ret2, *ret2, &ret2);
   printf("kernel_heap_top: 0x%x\n", kernel_heap_top);

   DougLea_free(ret);
   printf("free\n");
   printf("ret: 0x%x\n", ret);
   printf("*ret: 0x%x\n", *ret);
   printf("&ret: 0x%x\n", &ret);
   printf("kernel_heap_top: 0x%x\n", kernel_heap_top);

   int *ret3 = DougLea_malloc(0x100000);
   printf("malloc\n");
   printf("ret3: 0x%x\n", ret3);
   printf("*ret3: 0x%x\n", *ret3);
   printf("&ret3: 0x%x\n", &ret3);
   printf("kernel_heap_top: 0x%x\n", kernel_heap_top);

   DougLea_free(ret2);
   printf("free\n");
   printf("kernel_heap_top: 0x%x\n", kernel_heap_top);
   DougLea_free(ret3);
   printf("free\n");
   printf("kernel_heap_top: 0x%x\n", kernel_heap_top);
}
