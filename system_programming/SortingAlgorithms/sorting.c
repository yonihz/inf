#include "sorting.h"

static void SwapInt(int *a, int* b);
static int *MinElem(int *arr, size_t size);

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
    size_t count_arr_size = max - min + 1;
    int *count_arr = (int*)calloc(count_arr_size, sizeof(int));
    for (i = 0; i < size; ++i)
    {
        ++(count_arr[arr[i] - min]);
    }

    for (i = 1; i < count_arr_size; ++i)
    {
        count_arr[i] += count_arr[i - 1];
    }

    for (i = 0; i < size; ++i)
    {
        --(count_arr[arr[size - i - 1] - min]);
        dest[count_arr[arr[size - i - 1] - min]] = arr[size - i - 1];

    }

    free(count_arr);
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