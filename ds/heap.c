#include <stdlib.h> /* malloc */
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
    heap->vector = NULL;

    free(heap);
    heap = NULL;
}

size_t HeapSize(const heap_t *heap)
{
    assert(heap);

    return (VectorSize(heap->vector));
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
    void **first = NULL;
    void *temp = NULL;

    assert(heap);

    idx = VectorSize(heap->vector);
    status = VectorPushBack(heap->vector, &data);
    first = VectorGetItemAddress(heap->vector, 0);

    if (SUCCESS != status)
    {
        return (status);
    }

    temp = malloc(sizeof(void*));
    HeapifyUp(first, heap->cmp_func, idx, sizeof(void*), temp);
    free(temp);
    temp = NULL;
    
    return (status);
}


void HeapPop(heap_t *heap)
{
    void **first = NULL, **last = NULL;
    void *temp = NULL;

    assert(heap);

    first = VectorGetItemAddress(heap->vector, 0);
    last = VectorGetItemAddress(heap->vector, VectorSize(heap->vector) - 1);

    SwapPtr(first, last);
    VectorPopBack(heap->vector);
    first = VectorGetItemAddress(heap->vector, 0);
    temp = malloc(sizeof(void*));
    HeapifyDown(first , heap->cmp_func, 0, sizeof(void*), VectorSize(heap->vector), temp);
    free(temp);
    temp = NULL;
}


void *HeapPeek(const heap_t *heap)
{
    assert(heap);

    return *(void**)VectorGetItemAddress(heap->vector, 0);
}

void *HeapRemove(heap_t *heap, const void *data, match_func_t match_func)
{
    int is_found = 0;
    size_t idx = 0;
    void *to_remove_data = NULL, *temp = NULL;
    void **to_remove = NULL, **first = NULL, **last = NULL;

    assert(heap);

    for (idx = 0; (idx < VectorSize(heap->vector)) && (0 == is_found); ++idx)
    {
        to_remove = (void*)VectorGetItemAddress(heap->vector, idx);

        if (0 == match_func(data, *to_remove))
        {
            is_found = 1;
        }
    }

    if (0 == is_found)
    {
        return (NULL);
    }

    to_remove_data = *to_remove;
    last = VectorGetItemAddress(heap->vector, VectorSize(heap->vector) - 1);
    SwapPtr(to_remove, last);
    VectorPopBack(heap->vector);
    first = VectorGetItemAddress(heap->vector, 0);
    temp = malloc(sizeof(void*));
    HeapifyUp(first, heap->cmp_func, idx, sizeof(void*), temp);
    HeapifyDown(first, heap->cmp_func, idx, sizeof(void*), VectorSize(heap->vector), temp); 
    free(temp);
    temp = NULL;

    return (to_remove_data);
}

static void SwapPtr(void **ptr1, void **ptr2)
{
    void *temp = NULL;

    temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp; 
}