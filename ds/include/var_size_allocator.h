#ifndef _VAR_SIZE_ALLOCATOR_H_
#define _VAR_SIZE_ALLOCATOR_H_

/* version 0.4 */
/* date 25.09.19 */
/* time 12:40 */

#include <stddef.h> /*size_t*/

typedef struct var_alloc vsa_t;

/* O(N)
seg: the begining of the memory segment allocated by user
total_size: total size allocated by the user in bytes
return: the pointer to the memory management unit

- return null if the total size too small
- the return address and seg can be diffrent! 
    be carefull when you free the segment
- if the total_size is not enouth to initiate VSA - return NULL
*/
vsa_t *VSAInit(void *seg, size_t total_size);

/* O(N)
vsa: pointer to the memory management unit
return: the address of the allocated block 
if the block_size is zero - return NULL
*/ 
void* VSAAlloc(vsa_t *vsa, size_t block_size);

/* O(1)
block - the pointer of the block to free
if NULL pointer provided no action is taken
*/
void VSAFree(void *block);

/* O(N)
returns the size of the largest block avaliable
*/
size_t VSAGetLargestBlock(const vsa_t *vsa);

#endif