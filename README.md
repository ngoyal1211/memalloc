# memalloc
This program demonstrates the usage and efficiency of malloc, calloc, and realloc. The function (i) prints out  the heap start/end addresses and (ii) prints out the memory leaks in your code.

For the doubly linked list, I added a variable in the struct for the previous node and made sure to have every allocated block pointing to a previous block. To implement the best fit, I ordered the doubly linked list every time a block was created so it would be in the correct spot based on its size and changed the previous and next blocks to make sure it pointed to the right thing.
In the bonus, I did the best fit a little bit differently. Instead of keeping the doubly linked list ordered and finding the best block, I left the list unordered and traversed the whole list to find the best free block if there was one. To make it easier and have collapse work properly, I changed the best fit method back to using a non-ordered list. For split, I checked if the size left over after changing the block size to the requested size had enough room for the struct, and if it did, I created a new block and inserted right after the block that split in the list and changed the doubly linked list pointers. For collapse, I kind of did the opposite of what I did for split except I had to check if the block before was also free, and if so, I merged those two also. So essentially, it could possibly collapse three blocks in the same call, on both the sides of the freed block on the heap. The size of the collapsed block includes the size of the struct of the next block. All of my code works fine including the bonus parts, and the memory leaks reflect the differences in efficiency for each component.
For calculating the memory leak, I captured the start and end address of the heap, then got the difference in the addresses to figure out the size of the heap. I kept track of how many bytes were allocated and at the end I subtracted the number of bytes actually allocated from the size of the heap to determine the leak.

