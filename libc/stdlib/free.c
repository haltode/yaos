#ifdef __is_libk

#include <kernel/memory.h>

extern Node *free_space;

void kfree(void *ptr)
{
   /* Points to the header of the block */
   Node *new_block = (Node *) ptr - 1;

   /* Find the closest free space block to ptr */
   Node *block = free_space;
   /* while(block->next != NULL && block < new_block) */
   /*    block = block->next; */

   /* If ptr is next to the block, we merge them together */
   /* TODO */

   /* Otherwise, we simply free the block */
   new_block->next = block->next;
   new_block->prev = block;
   block->next = new_block;
}

#else

/* TODO: Implement system calls for free */

#endif
