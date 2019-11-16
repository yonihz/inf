/****************************************************************
* 																*
* FILE NAME: sorting.c								        	*
* 																*
* PURPOSE: Sort and search functions source file			    *
*                                                               *
* DATE: 11.11.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
****************************************************************/

#include <math.h>
#include <string.h>

#include "sorting.h"

#define WORD sizeof(size_t)

static int* CopyArr(int *dest, int *src, size_t size);
static void SwapInt(int *a, int* b);
static int *MinElem(int *arr, size_t size);
static int MaxVal(int *arr, size_t size);
static size_t CountDigits(int n);
static void SwapPtr(int **a, int** b);
static int Pow(int n, size_t base);
static int isPow2(int n);
static void RecMergeSort(int *dest, int *src, size_t start, size_t end);
static void MergeSubArrays(int *dest, int *src, size_t start, size_t end);
static void QuickSortRec(const void *base, ssize_t left, ssize_t right,
                            size_t elem_size, cmp_func_t cmp_func, void *temp);
static ssize_t QuickSortPartition(const void *base, ssize_t left, ssize_t right,
                                    size_t elem_size, cmp_func_t cmp_func, void *temp);
static void *BinSearchRec(const void *base, ssize_t left_idx, ssize_t right_idx, size_t elem_size,
                    const void *requested_data, cmp_func_t cmp_func);
static void SwapMemcpy(void *var1, void *var2, void *temp, size_t elem_size);

void BubbleSort(int *arr, size_t size)
{
    size_t i = 0;
    while (size > 1)
    {
        for (i = 0; i < size - 1; ++i)
        {
            if (arr[i] > arr[i + 1])
            {
                SwapInt(arr + i, arr + i + 1);
            }
        }
        --size;
    }
}

void InsertionSort(int *arr, size_t size)
{
    size_t i = 0, j = 0;
    for (i = 1; i < size; i++)
    {
        for (j = i; j > 0 && arr[j] < arr[j - 1]; --j)
        {
            SwapInt(arr + j, arr + j - 1);
        }
    }
}

void SelectionSort(int *arr, size_t size)
{
    size_t i = 0;
    for (i = 0; i < size; ++i)
    {
        SwapInt(arr + i, MinElem(arr + i, size - i));
    }
}

void CountingSort(int *arr, int *dest, size_t size, int min, int max)
{
    size_t i = 0;
    size_t count_size = max - min + 1;
    int *count = (int*)calloc(count_size, sizeof(int));
    for (i = 0; i < size; ++i)
    {
        ++(count[arr[i] - min]);
    }

    for (i = 1; i < count_size; ++i)
    {
        count[i] += count[i - 1];
    }

    for (i = 0; i < size; ++i)
    {
        --(count[arr[size - i - 1] - min]);
        dest[count[arr[size - i - 1] - min]] = arr[size - i - 1];

    }

    free(count);
}

void RadixSort(int *arr, size_t size, size_t base)
{
    size_t i = 0, n = 0, shift = 0;
    int *dest = (int*)calloc(size, sizeof(arr[0]));

    if (!isPow2(base))
    {    
        n = CountDigits(MaxVal(arr, size));
        for (i = 0; i < n; ++i)
        {
            shift = Pow(i, base);  
            CountingSortAnyBase(arr, dest, size, base, shift);
            SwapPtr(&arr, &dest);
        }
        CopyArr(dest, arr, size);
        /*free(dest);*/
    }
    else
    {        
        for (shift = 1, i = 0; shift < base; ++i)
        {
            shift <<= 1;
        }
        shift = i;
        n = sizeof(arr[0]) * WORD / shift;
        for (i = 0; i < n; ++i)
        {
            CountingSortBase2(arr, dest, size, base, shift * i);
            SwapPtr(&arr, &dest);
        }
        CopyArr(dest, arr, size);
        free(dest);
    }
}

void CountingSortAnyBase(int *arr, int *dest, size_t size, size_t base, size_t shift)
{
    size_t i = 0;
    int *count = (int*)calloc(base, sizeof(arr[0]));
    for (i = 0; i < size; ++i)
    {
        ++(count[(arr[i] / shift) % base]);
    }

    for (i = 1; i < base; ++i)
    {
        count[i] += count[i - 1];
    }

    for (i = 0; i < size; ++i)
    {
        --(count[(arr[size - i - 1] / shift) % base]);
        dest[count[(arr[size - i - 1] / shift) % base]] = arr[size - i - 1];
    }

    free(count);
}

void CountingSortBase2(int *arr, int *dest, size_t size, size_t base, size_t shift)
{
    size_t i = 0;
    int *count = (int*)calloc(base, sizeof(arr[0]));
    for (i = 0; i < size; ++i)
    {
        ++(count[(arr[i] >> shift) & (base - 1)]);
    }

    for (i = 1; i < base; ++i)
    {
        count[i] += count[i - 1];
    }

    for (i = 0; i < size; ++i)
    {
        --(count[(arr[size  - i - 1] >> shift) & (base - 1)]);
        dest[count[(arr[size - i - 1] >> shift) & (base - 1)]] = arr[size - i - 1];
    }

    free(count);
}

void MergeSort(int *dest, int *src, size_t size)
{
    RecMergeSort(dest, src, 0, size - 1);
}

static void RecMergeSort(int *dest, int *src, size_t start, size_t end)
{
    if (start < end)
    {
        RecMergeSort(dest, src, start, ((start + end) / 2));
        RecMergeSort(dest, src, ((start + end) / 2) + 1, end);
        MergeSubArrays(dest, src, start, end);
    }
}

static void MergeSubArrays(int *dest, int *src, size_t start, size_t end)
{
    size_t i = 0, j = 0, k = 0;
    
    i = start;
    j = ((start + end) / 2) + 1;
    k = start;
    
    while ((i <= ((start + end) / 2)) && (j <= end))
    {
        if (src[i] < src[j])
        {
            dest[k] = src[i];
            ++i;
        }
        else
        {
            dest[k] = src[j];
            ++j;
        }
        
        ++k;
    }

    while (i <= ((start + end) / 2))
    {
        dest[k] = src[i];
        ++i;
        ++k;  
    }

    while (j <= end)
    {
        dest[k] = src[j];
        ++j;
        ++k;  
    }

    k = start;

    for (k = start; k <= end; ++k)
    {
        src[k] = dest[k];
    }
}

void QuickSort(const void *base, size_t nelem, size_t elem_size, cmp_func_t cmp_func)
{
    void *temp = NULL;

    temp = malloc(elem_size);

    QuickSortRec(base, 0, nelem - 1, elem_size, cmp_func, temp);
    
    free(temp);
    temp = NULL;
}

static void QuickSortRec(const void *base, ssize_t left, ssize_t right,
                            size_t elem_size, cmp_func_t cmp_func, void *temp)
{
    ssize_t pivot = right;

    if (left < right)
    {
        pivot = QuickSortPartition(base, left, right, elem_size, cmp_func, temp);
        QuickSortRec(base, left, pivot - 1, elem_size, cmp_func, temp);
        QuickSortRec(base, pivot + 1, right, elem_size, cmp_func, temp);
    }
}

static ssize_t QuickSortPartition(const void *base, ssize_t left, ssize_t right,
                                    size_t elem_size, cmp_func_t cmp_func, void *temp)
{
    ssize_t i = 0, j = 0;
    void *pivot = NULL;

    pivot = (void*)((char*)base + right * elem_size);
    i = left - 1;

    for (j = left; j < right; ++j)
    {
        if (0 > cmp_func((void*)((char*)base + j * elem_size), pivot))
        {
            ++i;
            SwapMemcpy((void*)((char*)base + i * elem_size), (void*)((char*)base + j * elem_size), temp, elem_size);
        }
    }
    SwapMemcpy((void*)((char*)base + (i + 1) * elem_size), (void*)((char*)base + right * elem_size), temp, elem_size);
    
    return (i + 1);
}

void *BinSearchItr(const void *base, size_t nelem, size_t elem_size,
                    const void *requested_data, cmp_func_t cmp_func)
{
    ssize_t left_idx = 0, right_idx = 0, mid_idx = 0;
    void *mid_data = NULL;
    int cmp_res = 0;

    right_idx = (nelem - 1);

    while (left_idx <= right_idx)
    {
        mid_idx = (left_idx + right_idx) / 2;
        mid_data = (void*)((char*)base + mid_idx * elem_size);
        cmp_res = cmp_func(requested_data, mid_data);

        if (0 == cmp_res)
        {
            return (mid_data);
        }
        else if (cmp_res < 0)
        {
            right_idx = mid_idx;
        }
        else
        {
            left_idx = mid_idx + 1;
        }
    }

    return (NULL);
}

void *BinSearchR(const void *base, size_t nelem, size_t elem_size,
                    const void *requested_data, cmp_func_t cmp_func)
{
    return (BinSearchRec(base, 0, nelem - 1, elem_size, requested_data, cmp_func));
}

static void *BinSearchRec(const void *base, ssize_t left_idx, ssize_t right_idx, size_t elem_size,
                    const void *requested_data, cmp_func_t cmp_func)
{
    ssize_t mid_idx = 0;
    void *mid_data;
    int cmp_res = 0;

    if (left_idx > right_idx)
    {
        return (NULL);
    }

    mid_idx = (left_idx + right_idx) / 2;
    mid_data = (void*)((char*)base + mid_idx * elem_size);
    cmp_res = cmp_func(requested_data, mid_data);

    if (0 == cmp_res)
    {
        return (mid_data);
    }
    else if (0 > cmp_res)
    {
        right_idx = mid_idx;
    }
    else
    {
        left_idx = mid_idx + 1;
    }

    return BinSearchRec(base, left_idx, right_idx, elem_size, requested_data, cmp_func);
}

void *JumpSearchItr(const void *base, size_t nelem, size_t elem_size,
                    const void *requested_data, cmp_func_t cmp_func)
{
    size_t jump_size = 0, idx = 0, idx_next = 0;
    void *data = NULL;

    jump_size = sqrt(nelem);
    idx_next = idx + jump_size;
    data = (void*)((char*)base + idx_next * elem_size);

    while (0 < cmp_func(requested_data, data))
    {
        idx = idx_next;
        idx_next = idx + jump_size;
        data = (void*)((char*)base + idx_next * elem_size);

        if (idx_next > nelem)
        {
            idx_next = nelem;
            break;
        }
    }

    data = (void*)((char*)base + idx * elem_size);

    while (0 != cmp_func(requested_data, data))
    {
        ++idx;

        if (idx > idx_next)
        {
            return (NULL);
        }

        data = (void*)((char*)base + idx * elem_size);
    }

    return (data);
}

static void SwapInt(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

static int *MinElem(int *arr, size_t size)
{
    int *min_idx = arr;
    size_t i = 0;
    for (i = 1; i < size; ++i)
    {
        min_idx = (arr[i] < *min_idx) ? (arr + i) : min_idx;  
    }
    return (min_idx);
}

static int MaxVal(int *arr, size_t size)
{
    size_t i = 0;
    int max = arr[0];

    for (i = 0; i < size; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return (max);
}

static size_t CountDigits(int n)
{
    size_t i = 0;
    while (n)
    {
        i++;
        n /= 10;
    }
    return (i);
}

static void SwapPtr(int **a, int** b)
{
    int *temp = *a;
    *a = *b;
    *b = temp;
}

static int Pow(int n, size_t base)
{
    size_t num = 1;

    while (n)
    {
        num *= base;
        n--;
    }

    return (num);
}

static int isPow2(int n)
{
	if (0 == n)
	{
		return (0);
	}

	else if ((n & (n - 1)) == 0)
	{
		return (1);
	}

	return (0);	
}

static int* CopyArr(int *dest, int *src, size_t size)
{
    size_t i = 0;
    for (i = 0; i < size; ++i)
    {
        dest[i] = src[i];
    }

    return (dest);
}

static void SwapMemcpy(void *var1, void *var2, void *temp, size_t elem_size)
{
    memcpy(temp, var1, elem_size);
    memcpy(var1, var2, elem_size);
    memcpy(var2, temp, elem_size);
}