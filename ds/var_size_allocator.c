#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "var_size_allocator.h"

#ifndef NDEBUG
#define VALID_NODE 0xDEADBEEF
#endif

#define WORD (sizeof(ptrdiff_t))
#define NWORDS(x) (sizeof(x) / WORD)
#define TAIL_END(x) ((size_t)(x) % WORD)
#define TAIL_START(x) ((WORD - (size_t)(x) % WORD) % WORD)
#define ALIGN(x) ((x) + TAIL_START(x))

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
    node_vsa_t* first_node = NULL;
    void* seg_end = NULL;
    vsa_t* vsa = NULL;

    seg_end = (void*)((char*)seg + total_size);
    total_size = total_size - TAIL_START(seg) - TAIL_END(seg_end) 
                    - NWORDS(vsa_t) * WORD;

    if ((total_size / WORD) < (NWORDS(node_vsa_t) + 1))
    {
        return (NULL);
    }

    seg = (vsa_t*)((char*)seg + TAIL_START(seg));
    vsa = (vsa_t*)seg;
    vsa->total_size = total_size / WORD;
    first_node = (node_vsa_t*)((vsa_t*)seg + 1);
    first_node->offset = total_size / WORD - NWORDS(node_vsa_t);
    return (seg);
}

void* VSAAlloc(vsa_t* vsa, size_t block_size)
{
    node_vsa_t *curr = NULL, *next = NULL;
    ptrdiff_t wblock = 0, wnode = 0, wcount = 0;
  
    wblock = ALIGN(block_size) / WORD;
    wnode = NWORDS(node_vsa_t);
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
#ifndef NDEBUG
    curr->magic = VALID_NODE;
#endif
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

#ifndef NDEBUG
    assert(VALID_NODE == node_tofree->magic);
    node_tofree->magic = 0; 
#endif

    node_tofree->offset *= (-1);
}

size_t VSAGetLargestBlock(const vsa_t* vsa)
{
    node_vsa_t *curr = NULL, *next = NULL;
    ptrdiff_t wnode = 0, wcount = 0, largest = 0;

    wnode = NWORDS(node_vsa_t);
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
        curr->offset += (next->offset > 0) * (next->offset + wnode);
        largest = largest >= curr->offset ? largest : curr->offset;
        wcount += curr->offset + wnode;
    }
    return (largest * WORD);
}