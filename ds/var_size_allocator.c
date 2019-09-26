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
    total_tail = (word_size - total_size % word_size) % word_size;
    total_size = total_size - seg_tail - total_tail - nwords_vsa;
    nwords_free = total_size / word_size - nwords_node;

    if (nwords_free < 0)
    {
        return (NULL);
    }

    seg += seg_tail;
    vsa = (vsa_t*)seg;
    vsa->total_size = total_size;
    first_node = (node_vsa_t*)((vsa_t*)seg + 1);
    first_node->offset = nwords_free; 
    return (seg);
}

void* VSAAlloc(vsa_t* vsa, size_t block_size)
{
    node_vsa_t *curr_node = NULL, *next_node = NULL;
    ptrdiff_t word_size = sizeof(size_t);
    ptrdiff_t nwords_block = 0, nwords_node = 0, nbytes_count = 0;
    ptrdiff_t curr_offset = 0, nbytes_count = 0;

    if (0 == block_size)
    {
        return (NULL);
    }

    nwords_block = ((word_size - block_size % word_size) % word_size
                    + block_size) / word_size;
    nwords_node = sizeof(node_vsa_t) / word_size;
    curr_node = (node_vsa_t*)((vsa_t*)vsa + 1);
    curr_offset = curr_node->offset;
    nbytes_count = curr_offset + nwords_node;

    while ((nwords_block > curr_offset) && (nbytes_count <= vsa->total_size))
    {
        next_node =
        (node_vsa_t*)((void*)curr_node + nwords_node + curr_offset);

        if (next_node->offset > 0)
        {
            curr_node->offset += next_node->offset + nwords_node;
            next_node->offset = 0;
        }
        else
        {
            curr_node = next_node;
            curr_offset = curr_node->offset;
            nbytes_count += curr_offset;
        }
    }

    /* TODO: add loop to build next node with offset diff */
    /* TODO: add case if there's room for block but not for next node */

        return (nbytes_count < vsa->total_size) ? (curr_node + 1) : NULL;
}

void VSAFree(void *block)
{
    node_vsa_t* node_tofree = NULL;

    /* TODO: check DEADBEEF */

    if (NULL == block)
    {
        return;
    }

    node_tofree = (char*)block - sizeof(node_vsa_t);
    node_tofree->offset *= (-1);
}

size_t VSAGetLargestBlock(const vsa_t* vsa)
{

}

