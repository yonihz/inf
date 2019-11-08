#include <stdlib.h> /* malloc */
#include <string.h> /* memcpy */

#include "heapify.h"

/* TODO: remove nelements from signature */
void HeapifyUp(void *arr, cmp_func_t cmp_func, size_t idx, size_t size, size_t nelements)
{
    int cmp_res = 0;
    size_t idx_parent = 0;
    void **parent = NULL, **current = NULL, *temp = NULL;

    idx_parent = idx;

    while (idx == idx_parent && (idx > 0) && (nelements > 1))
    {
        idx_parent = (idx - 1) / 2;
        parent = (void*)((char*)arr + size * idx_parent);
        current = (void*)((char*)arr + size * idx);
        cmp_res = cmp_func(*current, *parent);

        if (cmp_res > 0)
        {
            temp = malloc(size);
            memcpy(temp, current, size);
            memcpy(current, parent, size);
            memcpy(parent, temp, size);
            free(temp);
            idx = idx_parent;
        }
    }
}

void HeapifyDown(void *arr, cmp_func_t cmp_func, size_t idx, size_t size, size_t nelements)
{
    int cmp_res = 0;
    size_t idx_left_child = 0, idx_right_child = 0, idx_greater_child = 0;
    void **left_child = NULL, **right_child = NULL;
    void **greater_child = NULL, **current = NULL, **temp = NULL;

    idx_greater_child = idx;

    while (idx == idx_greater_child && ((idx * 2 + 2) < nelements))
    {
        idx_left_child = idx * 2 + 1;
        idx_right_child = idx * 2 + 2;

        left_child = (void*)((char*)arr + size * idx_left_child);
        right_child = (void*)((char*)arr + size * idx_right_child);
        current = (void*)((char*)arr + size * idx);

        cmp_res = cmp_func(*left_child, *right_child);
        idx_greater_child = cmp_res > 0 ? idx_left_child : idx_right_child;
        greater_child = (void*)((char*)arr + size * idx_greater_child);

        cmp_res = cmp_func(*current, *greater_child);

        if (cmp_res < 0)
        {
            temp = malloc(size);
            memcpy(temp, current, size);
            memcpy(current, greater_child, size);
            memcpy(greater_child, temp, size);
            free(temp);
            idx = idx_greater_child;
        }
    }
}