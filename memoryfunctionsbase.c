// This implementation maintains an unordered singly linked list of all the blocks allocated

#include <memoryfunctions.h>

// The node for a singly linked list
struct block_meta {
    size_t size;
    struct block_meta *next;
    int free;
};
#define META_SIZE sizeof(struct block_meta)

// always points to the starting of the list
void *global_base = NULL;

// function to find the first free block which can accomodate the size requested
// Returns the free block found otherwise returns null
// The last variable is used as a pointer to return the current last node on the list
struct block_meta *find_free_block(struct block_meta **last, size_t size)
{
     struct block_meta *current = global_base;

     // loops through the list and breaks then a node is free and greater than size
     while (current && !(current->free && current->size >= size)) {
	  *last = current;
	  current = current->next;
     }
     return current;
}

// Always allocates new memory of size on the top of the heap and adds the new node to the end of the list indicated by the last node
struct block_meta *request_space(struct block_meta* last, size_t size)
{
     struct block_meta *block;
     block = sbrk(0);
     void *request = sbrk(size + META_SIZE);
     assert((void*)block == request); //Not thread safe.
     if (request == (void*) -1) {
	  return NULL; //sbrk failed
     }

     // add the new node to the end of the list
     if (last) { //NULL on first request
	 last->next = block;
     }
     block->size = size;
     block->next = NULL;
     block->free = 0;

     return block;
}

// allocates a memory block of size. It first looks to see if any of the blocks allocated on the heap has been made free otherwise grows the heap to allocate a new block
void *malloc(size_t size)
{
    struct block_meta *block;
    if (size <= 0) {
	 return NULL;
    }
    
    if (!global_base) { //First call
       block = request_space(NULL, size);
       if (!block) {
	    return NULL;
       }
       global_base = block;
    }
    else
    {
      struct block_meta *last = global_base;
      block = find_free_block(&last, size);
      //If failed to find free block, pass the last block on the list so the new block can be added to the end
      if (!block)  
      {
          block = request_space(last, size);
	  if (!block) {
	    return NULL;
	  }
      }
      else { //Found free block
	block->free = 0;
      }
    }
    return (block + 1);
}

// returns a ptr to the struct for the block
struct block_meta *get_block_ptr(void *ptr) {
    return (struct block_meta*)ptr - 1;
}

// free the block by marking it available
void free(void *ptr)
{
   if(!ptr) {
     return;
   }
   struct block_meta* block_ptr = get_block_ptr(ptr);
   assert (block_ptr->free == 0);
   block_ptr->free = 1;
}

// Allocate the memory for the new size. Free the old memory block if it is smaller than the new size requested
void *realloc(void *ptr, size_t size)
{
   if (!ptr)
   {
      //NULL ptr. realloc should act like malloc.
      return malloc(size);
   }

   struct block_meta* block_ptr = get_block_ptr(ptr);
   if (block_ptr->size >= size)
   {
      return ptr;
   }

   //Need to really realloc. Malloc new space and free old space.
   //Then copy old data to new space.
   void *new_ptr;
   new_ptr = malloc(size);
   if (!new_ptr)
   {
      return NULL;
   }
   memcpy(new_ptr, ptr, block_ptr->size);

   free(ptr);
   return new_ptr;
}

// allocates new memory and sets the value to 0 for each byte
void *calloc(size_t nelem, size_t elsize) 
{
    size_t size = nelem * elsize;
    void *ptr = malloc(size);
    memset(ptr, 0, size);
    return ptr;
}

