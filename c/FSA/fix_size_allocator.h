#ifndef _FIX_SIZE_ALLOCATOR_H_
#define _FIX_SIZE_ALLOCATOR_H_

/* version 1.1 */
/* date 23.09.19 */
/* time 18:00 */

#include <stddef.h> /*size_t*/

typedef struct allocator allocator_t;

/*O() 
block_size - the size of each unit in bytes
num_of_block - the max num of memomry blocks
return- the total size is needed to allocate by the user in bytes
*/
size_t FSASuggestSize(size_t block_size, size_t num_of_blocks);

/*O(n)
dest- the begining of the segment that allocated by the user
block_size- the size of each unit in bytes
total_size- the total size allocated by the user in bytes
return- the iter of the memory management unit
the begining of the segment that allocated. return null if the total size too small
the return address and dest can be diffrent! be carefull when you free the segment
*/
allocator_t* FSAInit(void* dest, size_t block_size, size_t total_size);

/* O(1)
allocator- in which segment do allocation
return- the address of the allocated block, if full return NULL
*/ 
void* FSAAlloc(allocator_t *allocator);

/*O(1)
block- the address of the block to free
*/
void FSAFree(void *block);

/*O(1)
allocator- which segment
return num of free blocks */
size_t FSACountFree(const allocator_t *allocator);

/*O(1)
allocator- which segment
return the size of each block */
size_t FSAGetBlockSize(const allocator_t *allocator);

#endif
