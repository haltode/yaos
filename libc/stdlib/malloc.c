#include <string.h>

#ifdef __is_libk

#include <kernel/memory.h>

extern Node *free_space;

void *kmalloc(size_t size)
{
   size_t nb_units = get_nb_units(size);

   /* Go through every free block in the heap */
   for(Node *block = free_space; block != NULL; block = block->next) {
      /* Perfect fit */
      if(block->size == nb_units)
         block->prev = block->next;
      /* Too big */
      if(block->size > nb_units)
         block->size -= nb_units;

      return (void *) (block + 1);
   }

   /* No more free space */
   /* TODO: allocate new space */
   return NULL;
}

#else

/* TODO: Implement system calls for malloc */

#endif
