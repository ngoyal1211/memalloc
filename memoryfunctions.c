// This implementation maintains an Ordered doubly linked list of all the blocks allocated

#include <memoryfunctions.h>

// the node for a double linked list
struct block_meta{
   size_t size;
   struct block_meta *prev;
   struct block_meta *next;
   int free;
};
#define META_SIZE sizeof(struct block_meta)

// always pint to the starting of the ordered list which is not necessarily the beginning of the heap
void *global_base = NULL;

// function to find the block on the list whose size is greater than size
// The list is ordered so the first free block found will be returned
// used to find where to insert the new node into the Ordered list
struct block_meta *findLocation(size_t size)
{
    struct block_meta *current = global_base;
    while(current && !(current->size >= size) && current->next)
    {
	current = current->next;
    }
    return current;
}

//starts at the base of the linked list and goes through the list, returns when it finds the first 
//free linked list of size greater than or equal to the requested size
// the list is ordered so the first block found will be the best fit
struct block_meta *find_free_block( size_t size)
{
    struct block_meta *current = global_base;
    while (current && !(current->free && current->size >= size))
    {
	  current = current->next;
    }
    return current;
}

// Always allocates new memory to the top of the heap and adds the new block as a node to the list
// The list is kept ordered in ascending order by size of the block
struct block_meta *request_space_best(size_t size)
{
    struct block_meta *block;
    block = sbrk(0);
    void *request = sbrk(size + META_SIZE);
    assert((void*)block == request); //Not thread safe.

    if (request == (void*) -1)
    {
	   return NULL; // sbrk failed.
    }
    struct block_meta *spot = findLocation(size);
    if (spot) //NULL on first request
    {
	if(spot->next == NULL && spot->size < size)//this means the new node should go to the end
	{
	     block->prev = spot;
	     spot->next = block;
	     block->next = NULL;
	}
	else
	{
	     block->prev = spot->prev;
	    if (block->prev != NULL)//the new node is not the first one
	    {
	        block->prev->next = block;
	    }
	    else
	    {
	        global_base = block;//resets the base if new node is the beginning of the linked list
	    }
           spot->prev = block;
           block->next = spot;
	}

    }
    else //this is the first one in the list 
    {
	block->prev = NULL;
	block->next = NULL;
    }
    block->size = size;
    block->free = 0;
    return block;
}

// allocates a memory block of size. It first looks to see if any of the blocks allocated on the heap has been made free otherwise grows the heap to allocate a new block on the heap
void *malloc(size_t size)
{
    struct block_meta *block;
    if (size <= 0)
    {
        return NULL;
    }
    if (!global_base) //malloc is being called for the first time
    {
	block = request_space_best(size);
	if (!block)
	{
            return NULL;
	}
	global_base = block;
    }
    else
    {
	block = find_free_block(size);
	if (!block) // no free block was found 
	{
            block = request_space_best(size);
	    if (!block)
	    {
		return NULL;
	    }
	}
	else
	{
            block->free = 0; //flag the block as no longer free 
	}
    }
    return (block + 1);//moves the pointer past the struct and returns the loactions which can be used by the caller
}

struct block_meta *get_block_ptr(void *ptr)
{
    return (struct block_meta*)ptr - 1;
}

// free the block by marking it available
void free(void *ptr)
{
    if(!ptr)
    {
        return;
    }
    struct block_meta* block_ptr = get_block_ptr(ptr);
    assert(block_ptr->free == 0);
    block_ptr->free = 1;
}

// Allocates the memory for the new size when the size is bigger and frees the old memory block
void *realloc(void *ptr, size_t size)
{
    if(!ptr)
    {
        return malloc(size);
    }
    struct block_meta* block_ptr = get_block_ptr(ptr);
    if (block_ptr->size >= size)
    {
        //We have enough space. Could free some once we implement split.
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
