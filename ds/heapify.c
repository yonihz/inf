#include "heapify.h"

void HeapifyUp(void *arr, cmp_func_t cmp_func, size_t idx, size_t size, size_t nelements)
{
    int cmp_res = 0;
    size_t idx_left = 0, idx_right = 0, idx_greater = 0;

    if ((idx * 2 + 2) < nelements)
    {
        idx_left = idx * 2 + 1;
        idx_right = idx * 2 + 1;
        cmp_res = cmp_func(arr + idx_left, arr + idx_right);
        idx_greater = cmp_res > 0 ? idx_left : idx_right;
    }
}

void HeapifyDown(void *arr, cmp_func_t cmp_func, size_t idx, size_t size, size_t nelements)
{

}