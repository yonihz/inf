/****************************************************************
* 																*
* FILE NAME: fix_size_allocator.c		            		    *
* 																*
* PURPOSE: FSA functions source file          		            *
*                                                               *
* DATE: 28.09.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
****************************************************************/

#include "fix_size_allocator.h"

#define WORD sizeof(size_t)
#define NWORDS(x) (sizeof(x) / WORD)
#define TAIL_END(x) ((size_t)(x) % WORD)
#define TAIL_START(x) ((WORD - (size_t)(x) % WORD) % WORD)
#define ALIGN(x) ((x) + TAIL_START(x))

struct allocator
{
    void **next_free;
    size_t block_size;
    size_t nblocks;
    size_t nfree;
};

size_t FSASuggestSize(size_t block_size, size_t num_of_blocks)
{
    size_t meta_size = 0, suggest_size = 0;
    
    meta_size = WORD;
    block_size = ALIGN(block_size);
    suggest_size = (block_size + meta_size) * num_of_blocks + 
                    sizeof(allocator_t) + (WORD - 1);
    suggest_size = (!block_size || !num_of_blocks) ? 0 : suggest_size;
    return (suggest_size);
}

allocator_t *FSAInit(void *dest, size_t block_size, size_t total_size)
{
    size_t meta_size = 0, dest_tail = 0, i = 0, ablock_size = 0;
    void **node = NULL;
    allocator_t *alloc = NULL;

    meta_size = WORD;
    dest_tail = TAIL_START(dest);
    dest = (void*)((char*)dest + dest_tail);
    ablock_size = ALIGN(block_size);

    alloc = (allocator_t*)dest;

    if (total_size < FSASuggestSize(block_size, 1))
    {
        return (NULL);
    }

    alloc->nblocks = (total_size - dest_tail - sizeof(allocator_t)) / 
                        (ablock_size + meta_size);

    alloc->block_size = block_size;
    alloc->nfree = alloc->nblocks;
    alloc->next_free = (void*)(alloc + 1);

    node = alloc->next_free;
    for (i = 0; i < alloc->nblocks; i++)
    {
        *node = (void*)((char*)node + ablock_size + meta_size);
        node = *node;
    }

    return (alloc);
}

void *FSAAlloc(allocator_t *allocator)
{
    void *block = NULL;
    void **meta_block = NULL;

    if (allocator->nfree == 0)
    {
        return (NULL);
    }

    meta_block = allocator->next_free;
    block = (void*)(meta_block + 1);
    allocator->next_free = *(meta_block);
    *(meta_block) = &(allocator->next_free);
    allocator->nfree -= 1;
    return (block);
}

void FSAFree(void *block)
{
    void **meta_block = NULL;
    allocator_t* alloc = NULL;

    meta_block = (void**)block - 1;
    alloc = (allocator_t*)(*meta_block);
    *meta_block = alloc->next_free;
    alloc->next_free = meta_block;
    alloc->nfree +=1;
}

size_t FSACountFree(const allocator_t *allocator)
{
    return (allocator->nfree);
}

size_t FSAGetBlockSize(const allocator_t *allocator)
{
    return (allocator->block_size);
}
