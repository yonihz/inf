#include <stdio.h>

#include "fix_size_allocator.h"

struct allocator
{
    void** next_free;
    size_t block_size;
    size_t nblocks;
    size_t nfree;
};

size_t FSASuggestSize(size_t block_size, size_t num_of_blocks)
{
    size_t word = 0, meta_size = 0, suggest_size = 0;
    
    word = sizeof(size_t);
    meta_size = word;
    block_size += (word - block_size % word) % word;
    suggest_size = (block_size + meta_size) * num_of_blocks + 
                    sizeof(allocator_t) + (word - 1);
    return (suggest_size);
}

allocator_t* FSAInit(void* dest, size_t block_size, size_t total_size)
{
    size_t word = 0, meta_size = 0, dest_tail = 0, i = 0, ablock_size = 0;
    void** node = NULL;
    allocator_t* alloc = NULL;

    word = sizeof(size_t);
    meta_size = word;
    dest_tail = (word - (size_t)dest % word) % word;
    dest = (void*)((char*)dest + dest_tail);
    ablock_size = block_size + (word - block_size % word) % word;

    alloc = (allocator_t*)dest;
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

void* FSAAlloc(allocator_t *allocator)
{
    void* block = NULL;
    void** meta_block = NULL;

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
    void** meta_block = NULL;
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