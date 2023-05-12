// This implementation maintains an doubly linked list in order of allocation of the block on the heap
// This also implements the split of a memory block in the case when a block being reused has size more than what is needed and can accomdate the space for the list node
// This implements the collapsing of adjacent memory blocks when they are free

#include <memoryfunctions.h>

// The node for a doubly linked list
struct block_meta{
   size_t size;
   struct block_meta *prev;
   struct block_meta *next;
   int free;
};
#define META_SIZE sizeof(struct block_meta)

// always points to the beginning and end of the list which is also the order of the heap
void *global_base = NULL;

// simply remove a node from the doubly linked list
void removeNode(struct block_meta* block)
{
    if (block->prev != NULL)
    {
	block->prev->next = block->next;
    }
    if (block->next != NULL)
	block->next->prev = block->prev;

    block->prev = NULL;
    block->next = NULL;
}

//collapse method to merge two adjacent free blocks, both after and before
//it is possible that a block became free with free blocks on both sides
void collapse(struct block_meta* collapse)
{
    //if block_ptr->next exists and it is free, combine the two size including the struct of next
    struct block_meta *next = collapse->next;
    struct block_meta *prev = collapse->prev;

    if (next && collapse->free == 1 && next->free == 1) // ensure both adjacent blocks on the heap are free
    {
        collapse->size = collapse->size + next->size + META_SIZE;

        //remove this next block from the list
        removeNode(next);
    }
    if (prev && collapse->free == 1 && prev->free == 1) // ensure both adjacent blocks on the heap are free
    {
        prev->size = prev->size + collapse->size + META_SIZE;

        //remove this next block from the list
        removeNode(collapse);
    }
}

// splits the block and creates a new block with the size unused in the current block
// assumes the block is big enough to split and accomadate 1 more than the block_meta
void split(struct block_meta *block, size_t newSize)
{
      char* temp = (char*) block;//declaring char* to do pointer arithmetic on bytes
      temp = temp + META_SIZE + newSize;
      struct block_meta *splitblock = (struct block_meta*) temp;
      splitblock->free = 1;
      splitblock->size = block->size - META_SIZE - newSize;
      splitblock->next = NULL;
      splitblock->prev = block;

      block->size = newSize;

      // insert the new split block immediately after
      if(block->next != NULL)
      {
         block->next->prev = splitblock;
         splitblock->next = block->next;
      }
      block->next = splitblock;

      // collapse the new split block which is free in case the block after it was also free
      collapse(splitblock);
}

//starts at the base of the linked list and goes through the entire list
//returns the free linked list of size greater than or equal to the requested size
// which is closest to the new size requested amongst the blocks on the list
// The last variable is used to return the last node of the current list
struct block_meta *find_free_block(struct block_meta **last, size_t size)
{
    struct block_meta *current = global_base;
    struct block_meta *best = NULL;
    size_t bestsize = 0;

    while (current)
    {
	if(current->free && current->size >= size)
	{
           // sets the best for the first iteration or when a new best is found
	   if ((bestsize == 0) || (current->size < bestsize))
	   {
	       bestsize = current->size;
	       best = current;
           }
	}
	*last = current;
        current = current->next;
    }
    return best;
}

// Always allocates new memory to the top of the heap and adds the new block as a node to the end of the list
struct block_meta *request_space_best(struct block_meta *last, size_t size)
{
    struct block_meta *block;
    block = sbrk(0);
    void *request = sbrk(size + META_SIZE);
    assert((void*)block == request); //Not thread safe.

    if (request == (void*) -1)
    {
	   return NULL; // sbrk failed.
    }

    if (last)
    {
	last->next = block;
	block->prev = last;
    }
    block->size = size;
    block->free = 0;
    block->next = NULL;

    return block;
}

// allocates a memory block of size. It first looks to see if any of the blocks allocated on the heap has been made free otherwise grows the heap to allocate a new heap
void *malloc(size_t size)
{
    struct block_meta *block;
    if (size <= 0)
    {
        return NULL;
    }
    if (!global_base) //malloc is being called for the first time
    {
	block = request_space_best(NULL, size);
	if (!block)
	{
            return NULL;
	}
	global_base = block;
    }
    else
    {
	struct block_meta *last = global_base;
	block = find_free_block(&last, size);
	if (!block) // no free block was found 
	{
            block = request_space_best(last, size);
	    if (!block)
	    {
		return NULL;
	    }
	}
	else
	{
            block->free = 0; //flag the block as no longer free 
	    if ((block->size - size) > META_SIZE) //will only split if the left over size is greater than size of the struct
	    {
		split(block, size);
	    }
	}
    }
    return (block + 1);//moves the pointer past the struct and returns the loactions which can be used by the caller
}

// returns a ptr to the struct for the block
struct block_meta *get_block_ptr(void *ptr)
{
    return (struct block_meta*)ptr - 1;
}

// free the block by maring it available
// collapse the freed block if the adjacent blocks are also free
void free(void *ptr)
{
    if(!ptr)
    {
        return;
    }
    struct block_meta* block_ptr = get_block_ptr(ptr);
    assert(block_ptr->free == 0);
    block_ptr->free = 1;
    collapse(block_ptr);
}

// Allocate the memory for the new size. Free the old memory block if it is smaller than the new size requested
void *realloc(void *ptr, size_t size)
{
    if(!ptr)
    {
        return malloc(size);
    }
    struct block_meta* block_ptr = get_block_ptr(ptr);
    if (block_ptr->size >= size)
    {
        //We have enough space
	if ((block_ptr->size - size) > META_SIZE) //will only split if the left over size is greater than size of the struct
	{
	    split(block_ptr, size);
	}
	return ptr;
    }
    //Need to really alloc. Malloc new space and free old pace.
    //Then copy old data to new space.
    void *new_ptr;
    new_ptr = malloc(size);
    if(!new_ptr)
    {
	return NULL;
    }
    memcpy(new_ptr, ptr, block_ptr->size);
    free(ptr);

    return new_ptr;
}

void* calloc(size_t nelem, size_t elsize)
{
    size_t size = nelem * elsize;
    void *ptr = malloc(size);
    memset(ptr, 0, size);
    return ptr;
}
