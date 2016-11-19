#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include <kernel/memory.h>
#include <kernel/paging.h>

Page_dir *current_dir = 0;
uint32_t current_dir_base_reg = 0;

extern void load_page_directory(void);
extern void enable_paging(void);


/*
 * Setup
 */

void virt_mem_init(void)
{
   /* Create the page directory */
   Page_dir *dir = (Page_dir *) phys_mem_alloc_frame();
   if(!dir)
      return;
   memset(dir, 0, sizeof(Page_dir));

   /* Create the first page table */
   Page_table *identity_table = (Page_table *) phys_mem_alloc_frame();
   if(!identity_table)
      return;
   memset(identity_table, 0, sizeof(Page_table));

   /* Create the kernel heap page table */
   Page_table *kernel_heap = (Page_table *) phys_mem_alloc_frame();
   if(!kernel_heap)
      return;
   memset(kernel_heap, 0, sizeof(Page_table));

   /* Init the kernel heap datastructure */
   init_kernel_heap();

   /* Identity map the first 4 MiB (our kernel starts at 1 MiB) */
   uint32_t phys_addr = 0x0;
   uint32_t virt_addr = 0x0;
   for(size_t i = 0; i < ENTRY_PER_TABLE; ++i) {
      /* Create the page and set it */
      uint32_t *page = &identity_table->entry[pt_index(virt_addr)];
      pt_entry_set_frame(page, phys_addr);
      pt_entry_add_flags(page, PTE_PRESENT_BIT);

      phys_addr += PAGE_SIZE;
      virt_addr += PAGE_SIZE;
   }
   /* Identity map the next 4 MiB for our kernel heap */
   for(size_t i = 0; i < ENTRY_PER_TABLE; ++i) {
      uint32_t *page = &kernel_heap->entry[pt_index(virt_addr)];
      pt_entry_set_frame(page, phys_addr);
      pt_entry_add_flags(page, PTE_PRESENT_BIT);

      phys_addr += PAGE_SIZE;
      virt_addr += PAGE_SIZE;
   }

   /* Put the tables in the page directory */
   virt_mem_setup_page_dir_entry(dir, identity_table, 0x0);
   virt_mem_setup_page_dir_entry(dir, kernel_heap, 0x400000); /* 4 MiB */

   virt_mem_switch_page_dir(dir); 
   paging_setup();
   enable_paging();
}

/*
 * Kernel Heap
 */

/* The free space in the virtual memory is a linked list */
Node *free_space;

void init_kernel_heap(void)
{
   free_space = (Node *) KERNEL_HEAP_ADDR;
   free_space->next = NULL;
   free_space->prev = NULL;
   free_space->size = get_nb_units(KERNEL_HEAP_SIZE);
}

/* Each block of free space in the kernel heap is measured in
   units instead of bytes, where a unit represents the header
   of the block (pointers + size) */
size_t get_nb_units(size_t byte_size)
{
   return (byte_size + sizeof(Node) - 1) / sizeof(Node);
}

/*
 * Allocation/Deallocation
 */

bool virt_mem_alloc_page(uint32_t *pt_entry)
{
   /* Allocate the new frame */
   void *frame = phys_mem_alloc_frame();
   if(!frame)
      return false;

   /* Set up the frame in the page table entry */
   pt_entry_set_frame(pt_entry, (uint32_t)frame);
   pt_entry_add_flags(pt_entry, PTE_PRESENT_BIT);

   return true;
}

void virt_mem_free_page(uint32_t *pt_entry)
{
   /* Free the frame */
   void *frame = (void *) pt_entry_get_frame(*pt_entry);
   if(frame)
      phys_mem_free_frame(frame);

   /* Clear the page table entry */
   pt_entry_del_flags(pt_entry, PTE_PRESENT_BIT);
}

/*
 * Mapping
 */

void virt_mem_map_page(void *physical, void *virtual)
{
   /* Get the page directory */
   Page_dir *dir = virt_mem_get_dir();

   /* Get the page directory entry */
   uint32_t dir_index = pd_index((uint32_t) virtual);
   uint32_t *pd_entry = &dir->entry[dir_index];

   /* Check if the page table is valid (allocated and present) */
   if((*pd_entry & PTE_PRESENT_BIT) != PTE_PRESENT_BIT) {
      /* The page table is not valid, we need to create one */

      /* Allocate the table */
      Page_table *new_table = (Page_table *) phys_mem_alloc_frame();
      if(!new_table)
         return;

      /* Clear the table */
      memset(new_table, 0, sizeof(Page_table));

      /* Set up the new page directory entry */
      uint32_t *new_pd_entry = &dir->entry[dir_index];
      pd_entry_add_flags(new_pd_entry, PDE_PRESENT_BIT);
      pd_entry_add_flags(new_pd_entry, PDE_WRITABLE_BIT);
      pd_entry_set_frame(new_pd_entry, (uint32_t) new_table);
   }

   /* Get the page table */
   Page_table *table = (Page_table *) pd_entry_phys_addr(pd_entry);

   /* Get the page */
   uint32_t *page = &table->entry[pt_index((uint32_t) virtual)];

   /* Map the page and mark it as present */
   pt_entry_set_frame(page, (uint32_t) physical);
   pt_entry_add_flags(page, PTE_PRESENT_BIT);
}

/*
 * Page directory related
 */

Page_dir *virt_mem_get_dir(void)
{
   return current_dir;
}

void virt_mem_setup_page_dir_entry( Page_dir *dir,
                                    Page_table *table, uint32_t address)
{
   uint32_t *pd_entry = &dir->entry[pd_index(address)];
   pd_entry_add_flags(pd_entry, PDE_PRESENT_BIT);
   pd_entry_add_flags(pd_entry, PDE_WRITABLE_BIT);
   pd_entry_set_frame(pd_entry, (uint32_t)table);
}

void virt_mem_switch_page_dir(Page_dir *dir)
{
   current_dir = dir;
   current_dir_base_reg = (uint32_t) &dir->entry;
   load_page_directory();
}
