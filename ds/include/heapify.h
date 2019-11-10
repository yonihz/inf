#ifndef _HEAPIFY_H_OL74_
#define _HEAPIFY_H_OL74_

#include <stddef.h>

#include "heap.h"

void HeapifyUp(void *base, cmp_func_t cmp_func, size_t idx, size_t size_elem, void *temp);

void HeapifyDown(void *base, cmp_func_t cmp_func, size_t idx, size_t size_elem,
                    size_t nelements, void *temp);

#endif /* _HEAPIFY_H_OL74_ */
