#ifndef _HEAPIFY_H_OL74_
#define _HEAPIFY_H_OL74_

#include <stddef.h>

#include "heap.h"

void HeapifyUp(void *arr, cmp_func_t cmp_func, size_t idx, size_t size, size_t nelements);

void HeapifyDown(void *arr, cmp_func_t cmp_func, size_t idx, size_t size, size_t nelements);

#endif /* _HEAPIFY_H_OL74_ */
