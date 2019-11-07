#include <stdlib.h> /* malloc */
#include <string.h> /* memcpy */

#include "heapify.h"

/* TODO: remove nelements from signature */
void HeapifyUp(void *arr, cmp_func_t cmp_func, size_t idx, size_t size, size_t nelements)
{
    int cmp_res = 0;
    size_t idx_parent = 0;
    void *parent = NULL, *current = NULL, *temp = NULL;

    idx_parent = idx;

    while (idx == idx_parent && (idx > 0) && (nelements != 1))
    {
        idx_parent = (idx - 1) / 2;
        parent = (void*)((char*)arr + size * idx_parent);
        current = (void*)((char*)arr + size * idx);
        cmp_res = cmp_func(current, parent);

        if (cmp_res > 0)
        {
            temp = malloc(size);
            memcpy(temp, current, size);
            memcpy(current, parent, size);
            memcpy(parent, temp, size);
            
            idx = idx_parent;
        }
    }
}

void HeapifyDown(void *arr, cmp_func_t cmp_func, size_t idx, size_t size, size_t nelements)
{
    int cmp_res = 0;
    size_t idx_left = 0, idx_right = 0, idx_greater_child = 0;
    void *child_left = NULL, *child_right = NULL;
    void *child_greater = NULL, *current = NULL, *temp = NULL;

    idx_greater_child = idx;

    while (idx == idx_greater_child && ((idx * 2 + 1) < nelements))
    {
        idx_left = idx * 2 + 1;
        idx_right = idx * 2 + 2;
        child_left = (void*)((char*)arr + size * idx_left);
        child_right = (void*)((char*)arr + size * idx_right);
        current = (void*)((char*)arr + size * idx);

        if ((idx * 2 + 2) < nelements) /* has right child */
        {
            cmp_res = cmp_func(child_left, child_right);
            idx_greater_child = cmp_res > 0 ? idx_left : idx_right;
        }
        else
        {
            idx_greater_child = idx_left; 
        }

        child_greater = (void*)((char*)arr + size * idx_greater_child);
        cmp_res = cmp_func(current, child_greater);

        if (cmp_res < 0)
        {
            temp = malloc(size);
            memcpy(temp, current, size);
            memcpy(current, child_greater, size);
            memcpy(child_greater, temp, size);
            
            idx = idx_greater_child;
        }
    }
}