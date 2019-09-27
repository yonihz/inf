#include <stdio.h>
#include <stdlib.h>

#include "var_size_allocator.h"

/* Offset convention: used (-) / free (+), type is ptrdiff_t */
struct node_vsa
{
    ptrdiff_t offset;
#ifndef NDEBUG
    ptrdiff_t magic;
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
    ptrdiff_t seg_tail = 0, total_tail = 0;
    node_vsa_t* first_node = NULL;
    vsa_t* vsa = NULL;

    word_size = sizeof(size_t);
    nwords_node = sizeof(node_vsa_t) / word_size;
    nwords_vsa = sizeof(vsa_t) / word_size;
    seg_tail = (word_size - (size_t)seg % word_size) % word_size;
    total_tail = total_size % word_size;
    total_size = total_size - seg_tail - total_tail - nwords_vsa * word_size;
    nwords_free = total_size / word_size;

    if (nwords_free < nwords_node + 1)
    {
        return (NULL);
    }

    seg = (vsa_t*)((char*)seg + seg_tail);
    vsa = (vsa_t*)seg;
    vsa->total_size = nwords_free;
    first_node = (node_vsa_t*)((vsa_t*)seg + 1);
    first_node->offset = nwords_free - nwords_node;
    return (seg);
}

void* VSAAlloc(vsa_t* vsa, size_t block_size)
{
    node_vsa_t *curr = NULL, *next = NULL;
    ptrdiff_t word = sizeof(size_t);
    ptrdiff_t wblock = 0, wnode = 0, wcount = 0;

    if (0 == block_size)
    {
        return (NULL);
    }
  
    wblock = ((word - block_size % word) % word + block_size) / word; 
    wnode = sizeof(node_vsa_t) / word;
    curr = (node_vsa_t*)((vsa_t*)vsa + 1);
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

        curr->offset += next->offset + wnode;
        wcount += curr->offset + wnode;
        if (wblock <= curr->offset)
        {
            break;
        }
    }

    if (wblock > curr->offset)
    {
        return (NULL);
    }

    if (wblock < (curr->offset - wnode))
    {
        next = (node_vsa_t*)((ptrdiff_t*)curr + wnode + wblock + curr->offset);
        next->offset = curr->offset - wblock - wnode;
        curr->offset = wblock;
    }
    curr->offset *= (-1);
    return (curr + 1);
}

void VSAFree(void *block)
{
    node_vsa_t* node_tofree = NULL;

    /* TODO: check DEADBEEF */

    if (NULL == block)
    {
        return;
    }

    node_tofree = (node_vsa_t*)((char*)block - sizeof(node_vsa_t));
    node_tofree->offset *= (-1);
}

size_t VSAGetLargestBlock(const vsa_t* vsa)
{
    node_vsa_t *curr_node = NULL, *next_node = NULL;
    ptrdiff_t word_size = sizeof(size_t);
    ptrdiff_t nwords_node = 0, nbytes_count = 0, largest = 0;

    nwords_node = sizeof(node_vsa_t) / word_size;
    curr_node = (node_vsa_t*)((vsa_t*)vsa + 1);
    largest = (curr_node->offset > 0) ? curr_node->offset : 0;
    nbytes_count = labs(curr_node->offset) + nwords_node;

    while (nbytes_count < vsa->total_size)
    {
        next_node = (node_vsa_t*)((ptrdiff_t*)curr_node + nwords_node + curr_node->offset);
        
        if (next_node->offset < 0)
        {
            curr_node = next_node;
            nbytes_count += (-1) * curr_node->offset + nwords_node;
            continue;
        }
        curr_node->offset = next_node->offset + nwords_node;

        largest = largest >= curr_node->offset ? largest : curr_node->offset; 
    }
    printf("largest %lu\n", largest);
    return (largest * word_size);
}

