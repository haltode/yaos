#include <stddef.h>

#ifdef __is_libk

#include <kernel/memory.h>

extern Node *free_space;

void *kmalloc(size_t size)
{
   /* TODO: check the size given in parameter */

   /* Calculate the amount of units needed and add one for the header */
   size_t nb_units = get_nb_units(size) + 1;

   /* Go through every free block in the heap */
   for(Node *block = free_space; block != NULL; block = block->next) {
      /* Perfect fit */
      if(block->size == nb_units)
         block->prev = block->next;
      /* Too big */
      if(block->size > nb_units) {
         block->size -= nb_units;
         block += block->size;
         block->size = nb_units;
      }

      return (void *) (block + 1);
   }

   /* No more free space */
   /* TODO: allocate new space */
   return NULL;
}

#else

/* TODO: Implement system calls for malloc */

#endif
