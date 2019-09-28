#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "var_size_allocator.h"

#define VALID 0xDEADBEEF

/* Offset convention: used (-) / free (+), type is ptrdiff_t */
struct node_vsa
{
    ptrdiff_t offset;
#ifndef NDEBUG
    size_t magic;
#endif
};

typedef struct node_vsa node_vsa_t; 

/* total_size = allocated - align_tails - sizeof(vsa_t) */
struct var_alloc
{
    ptrdiff_t total_size;
};

vsa_t* VSAInit(void* seg, size_t total_size)
{
    ptrdiff_t word_size = 0;
    ptrdiff_t nwords_node, nwords_vsa = 0, nwords_free = 0;
    ptrdiff_t seg_tail = 0, seg_head = 0;
    node_vsa_t* first_node = NULL;
    vsa_t* vsa = NULL;

    word_size = sizeof(size_t);
    nwords_node = sizeof(node_vsa_t) / word_size;
    nwords_vsa = sizeof(vsa_t) / word_size;
    seg_tail = (word_size - (size_t)seg % word_size) % word_size;
    seg_head = ((size_t)seg + total_size) % word_size;
    total_size = total_size - seg_tail - seg_head - nwords_vsa * word_size;
    printf("total size %ld\n",total_size);
    nwords_free = total_size / word_size;

    if (nwords_free < nwords_node + 1)
    {
        return (NULL);
    }

    seg = (vsa_t*)((char*)seg + seg_tail);
    vsa = (vsa_t*)seg;
    vsa->total_size = nwords_free;
    first_node = (node_vsa_t*)((vsa_t*)seg + 1);
    first_node->magic = VALID;
    first_node->offset = nwords_free - nwords_node;
    return (seg);
}

void* VSAAlloc(vsa_t* vsa, size_t block_size)
{
    node_vsa_t *curr = NULL, *next = NULL;
    ptrdiff_t word = sizeof(size_t);
    ptrdiff_t wblock = 0, wnode = 0, wcount = 0;
  
    wblock = ((word - block_size % word) % word + block_size) / word; 
    wnode = sizeof(node_vsa_t) / word;
    curr = (node_vsa_t*)((vsa_t*)vsa + 1);
    wcount = labs(curr->offset) + wnode;
    while (wcount < vsa->total_size && wblock >= curr->offset)
    {
        next = (node_vsa_t*)((ptrdiff_t*)curr + wnode + labs(curr->offset));
        /* if next space is used, continue to next */
        if (curr->offset < 0)
        {
            curr = next;
            wcount += (-1) * curr->offset + wnode;
            continue;
        }
        /* defrag current and next spaces */
        curr->offset += (next->offset > 0) * (next->offset + wnode);
        wcount += curr->offset + wnode;
    }
    /* return NULL if not enough space was found */
    if (wblock > curr->offset || 0 == block_size)
    {
        return (NULL);
    }
    /* if enough free space, create another free space */ 
    if (wblock < (curr->offset - wnode))
    {
        next = (node_vsa_t*)((ptrdiff_t*)curr + wnode + wblock);
        next->offset = curr->offset - wblock - wnode;
        curr->offset = wblock;
    }
    curr->offset *= (-1);
    curr->magic = VALID;
    return (curr + 1);
}

void VSAFree(void *block)
{
    node_vsa_t* node_tofree = NULL;

    if (NULL == block)
    {
        return;
    }

    node_tofree = (node_vsa_t*)block - 1;

    assert(VALID == node_tofree->magic);

#ifndef NDEBUG
   node_tofree->magic = 0; 
#endif

    node_tofree->offset *= (-1);
}

size_t VSAGetLargestBlock(const vsa_t* vsa)
{
    node_vsa_t *curr = NULL, *next = NULL;
    ptrdiff_t word = sizeof(size_t);
    ptrdiff_t wnode = 0, wcount = 0, largest = 0;

    wnode = sizeof(node_vsa_t) / word;
    curr = (node_vsa_t*)((vsa_t*)vsa + 1);
    largest = (curr->offset > 0) ? curr->offset : 0;
    wcount = labs(curr->offset) + wnode;

    while (wcount < vsa->total_size)
    {
        next = (node_vsa_t*)((ptrdiff_t*)curr + wnode + curr->offset);
        
        if (next->offset < 0)
        {
            curr = next;
            wcount += (-1) * curr->offset + wnode;
            continue;
        }
        curr->offset = next->offset + wnode;
        largest = largest >= curr->offset ? largest : curr->offset; 
    }
    return (largest * word);
}