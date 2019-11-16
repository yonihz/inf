/****************************************************************
* 																*
* FILE NAME: heapify.c						    				*
* 																*
* PURPOSE: Heapify functions source file		    			*
*                                                               *
* DATE: 08.11.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
****************************************************************/

#include <stdlib.h> /* malloc */
#include <string.h> /* memcpy */

#include "heapify.h"

static void SwapMemcpy(void *var1, void *var2, void *temp, size_t elem_size);

void HeapifyUp(void *base, cmp_func_t cmp_func, size_t idx, size_t size_elem, void *temp)
{
    int cmp_res = 0;
    size_t idx_parent = 0;
    void **parent = NULL, **current = NULL;

    idx_parent = idx;

    while (idx == idx_parent && (idx > 0))
    {
        idx_parent = (idx - 1) / 2;
        parent = (void*)((char*)base + size_elem * idx_parent);
        current = (void*)((char*)base + size_elem * idx);
        cmp_res = cmp_func(*current, *parent);

        if (cmp_res > 0)
        {
            SwapMemcpy(current, parent, temp, size_elem);
            idx = idx_parent;
        }
    }
}

void HeapifyDown(void *base, cmp_func_t cmp_func, size_t idx, size_t size_elem,
                    size_t nelements, void *temp)
{
    int cmp_res = 0;
    size_t idx_left_child = 0, idx_right_child = 0, idx_greater_child = 0;
    void **left_child = NULL, **right_child = NULL;
    void **greater_child = NULL, **current = NULL;

    idx_greater_child = idx;

    while (idx == idx_greater_child && ((idx * 2 + 2) < nelements))
    {
        idx_left_child = idx * 2 + 1;
        idx_right_child = idx * 2 + 2;

        left_child = (void*)((char*)base + size_elem * idx_left_child);
        right_child = (void*)((char*)base + size_elem * idx_right_child);
        current = (void*)((char*)base + size_elem * idx);

        cmp_res = cmp_func(*left_child, *right_child);
        idx_greater_child = cmp_res > 0 ? idx_left_child : idx_right_child;
        greater_child = (void*)((char*)base + size_elem * idx_greater_child);

        cmp_res = cmp_func(*current, *greater_child);

        if (cmp_res < 0)
        {
            SwapMemcpy(current, greater_child, temp, size_elem);
            idx = idx_greater_child;
        }
    }
}

static void SwapMemcpy(void *var1, void *var2, void *temp, size_t elem_size)
{
    memcpy(temp, var1, elem_size);
    memcpy(var1, var2, elem_size);
    memcpy(var2, temp, elem_size);
}