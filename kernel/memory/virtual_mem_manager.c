#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <kernel/memory.h>
#include <kernel/paging.h>

struct page_dir *current_dir = 0;
uint32_t current_dir_base_reg = 0;

extern void load_page_directory(void);
extern void enable_paging(void);


/* Return the index of the page directory entry given a virtual address */
static uint32_t page_directory_index(uint32_t address)
{
   return address >> 22;
}

/* Return the index of the page table entry (table/dir) given a virtual address */
static uint32_t page_table_index(uint32_t address)
{
   return (address >> 12) & 0x3FF;
}

static uint32_t get_pd_entry_phys_address(uint32_t *entry)
{
   return *entry & ~0xFFF;
}

static void virt_mem_switch_page_dir(struct page_dir *dir)
{
   current_dir = dir;
   current_dir_base_reg = (uint32_t) &dir->entry;
   load_page_directory();
}

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

uint32_t *virt_mem_lookup_pt_entry(struct page_table *table, uint32_t address)
{
   if(table)
      return &table->entry[page_table_index(address)];
   return 0;
}

uint32_t *virt_mem_lookup_pd_entry(struct page_dir *dir, uint32_t address)
{
   if(dir)
      return &dir->entry[page_table_index(address)];
   return 0;
}

struct page_dir *virt_mem_get_dir(void)
{
   return current_dir;
}

void virt_mem_map_page(void *physical, void *virtual)
{
   /* Get the page directory */
   struct page_dir *dir = virt_mem_get_dir();

   /* Get the page directory entry */
   uint32_t dir_index = page_directory_index((uint32_t) virtual);
   uint32_t *pd_entry = &dir->entry[dir_index];

   /* Check if the page table is valid (allocated and present) */
   if((*pd_entry & PTE_PRESENT_BIT) != PTE_PRESENT_BIT) {
      /* The page table is not valid, we need to create one */

      /* Allocate the table */
      struct page_table *new_table = (struct page_table*) phys_mem_alloc_frame();
      if(!new_table)
         return;

      /* Clear the table */
      memset(new_table, 0, sizeof(struct page_table));

      /* Set up the new page directory entry */
      uint32_t *new_pd_entry = &dir->entry[dir_index];
      pd_entry_add_flags(new_pd_entry, PDE_PRESENT_BIT);
      pd_entry_add_flags(new_pd_entry, PDE_WRITABLE_BIT);
      pd_entry_set_frame(new_pd_entry, (uint32_t) new_table);
   }

   /* Get the page table */
   struct page_table *table = (struct page_table*) get_pd_entry_phys_address(pd_entry);

   /* Get the page */
   uint32_t *page = &table->entry[page_table_index((uint32_t) virtual)];

   /* Map the page and mark it as present */
   pt_entry_set_frame(page, (uint32_t) physical);
   pt_entry_add_flags(page, PTE_PRESENT_BIT);
}

void virt_mem_setup_page_table(  struct page_table *table,
                                 uint32_t phys_addr, uint32_t virt_addr)
{
   /* Clear the page table */
   memset(table, 0, sizeof(struct page_table));

   /* Fill the page table */
   uint32_t phys = phys_addr;
   uint32_t virt = virt_addr;
   for(size_t i = 0; i < ENTRY_PER_TABLE; ++i) {
      /* Create the page and set it */
      uint32_t *page = &table->entry[page_table_index(virt)];
      pt_entry_set_frame(page, phys);
      pt_entry_add_flags(page, PTE_PRESENT_BIT);

      phys += PAGE_SIZE;
      virt += PAGE_SIZE;
   }
}

void virt_mem_setup_page_dir_entry( struct page_dir *dir,
                                    struct page_table *table, uint32_t address)
{
   uint32_t *pd_entry = &dir->entry[page_directory_index(address)];
   pd_entry_add_flags(pd_entry, PDE_PRESENT_BIT);
   pd_entry_add_flags(pd_entry, PDE_WRITABLE_BIT);
   pd_entry_set_frame(pd_entry, (uint32_t)table);
}

void virt_mem_init(void)
{
   /* Create the table */
   struct page_table *identity_table = (struct page_table *) phys_mem_alloc_frame();
   if(!identity_table)
      return;

   /* Create the page directory */
   struct page_dir *dir = (struct page_dir *) phys_mem_alloc_frames(3);
   if(!dir)
      return;
   memset(dir, 0, sizeof(struct page_dir));

   /* Identity map the first 4 MiB */
   virt_mem_setup_page_table(identity_table, 0x0, 0x0);
   
   /* Put the table in the page directory */
   virt_mem_setup_page_dir_entry(dir, identity_table, 0x0);

   virt_mem_switch_page_dir(dir); 
   paging_setup();
   enable_paging();
}
