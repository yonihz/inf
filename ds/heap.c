#include <stdlib.h>
#include <assert.h>

#include "heap.h"
#include "heapify.h"
#include "vector.h"

#define SUCCESS 0

struct heap
{
    cmp_func_t cmp_func;
    vector_t *vector;
};

static void SwapPtr(void **ptr1, void **ptr2);

heap_t *HeapCreate(cmp_func_t cmp_func)
{
   heap_t *heap = NULL;

   heap = (heap_t*)malloc(sizeof(heap_t));

    if (NULL == heap)
    {
        return (NULL);
    }

   heap->vector = VectorCreate(sizeof(void*), 1);
   heap->cmp_func = cmp_func;

   return (heap); 
}


void HeapDestroy(heap_t *heap)
{
    assert(heap);

    VectorDestroy(heap->vector);
    free(heap);
    heap = NULL;
}

size_t HeapSize(const heap_t *heap)
{
    assert(heap);

    return VectorSize(heap->vector);
}


int HeapIsEmpty(const heap_t *heap)
{
    assert(heap);

    return (VectorSize(heap->vector) == 0);
}


int HeapPush(heap_t *heap, void *data)
{
    size_t idx = 0;
    int status = 0;

    assert(heap);

    idx = VectorSize(heap->vector) - 1;
    status = VectorPushBack(heap->vector, data);

    if (SUCCESS != status)
    {
        return (status);
    }

    HeapifyUp(heap->vector, heap->cmp_func, idx, sizeof(void*), VectorSize(heap->vector));

    return (status);
}


void HeapPop(heap_t *heap)
{
    void **first = NULL, **last = NULL;

    assert(heap);

    first = VectorGetItemAddress(heap->vector, 0);
    last = VectorGetItemAddress(heap->vector, VectorSize(heap->vector) - 1);

    SwapPtr(first, last);
    VectorPopBack(heap->vector);
    HeapifyDown(heap->vector, heap->cmp_func, 0, sizeof(void*), VectorSize(heap->vector));
}


void *HeapPeek(const heap_t *heap)
{
    assert(heap);

    /* TODO: should be void**? */
    return VectorGetItemAddress(heap->vector, 0);
}

void *HeapRemove(heap_t *heap, const void *data, match_func_t match_func)
{
    size_t idx = 0;
    void *idx_data = NULL;
    void **idx_Addr = NULL, **last = NULL;

    assert(heap);

    while (0 != match_func(data, *(void**)VectorGetItemAddress(heap->vector, idx)))
    {
        idx += 1;
    }

    idx_Addr = VectorGetItemAddress(heap->vector, idx);
    last = VectorGetItemAddress(heap->vector, VectorSize(heap->vector) - 1);
    SwapPtr(idx_Addr, last);

    idx_data = *(void**)VectorGetItemAddress(heap->vector, idx);

    HeapifyUp(heap->vector, heap->cmp_func, idx, sizeof(void*), VectorSize(heap->vector));
    HeapifyDown(heap->vector, heap->cmp_func, idx, sizeof(void*), VectorSize(heap->vector)); 
    
    VectorPopBack(heap->vector);
    return (idx_data);
}

static void SwapPtr(void **ptr1, void **ptr2)
{
    void *temp = NULL;

    temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp; 
}