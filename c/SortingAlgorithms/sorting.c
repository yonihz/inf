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
static ssize_t QuickSortPartition(int *arr, ssize_t left, ssize_t right);

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

void QuickSort(int *arr, ssize_t left, ssize_t right)
{
    ssize_t pivot = right;

    if (left < right)
    {
        pivot = QuickSortPartition(arr, left, right);
        QuickSort(arr, left, pivot - 1);
        QuickSort(arr, pivot + 1, right);
    }
}

static ssize_t QuickSortPartition(int *arr, ssize_t left, ssize_t right)
{
    ssize_t i = 0, j = 0;
    int pivot = 0;

    pivot = arr[right];
    i = left - 1;

    for (j = left; j < right; ++j)
    {
        if (arr[j] < pivot)
        {
            ++i;
            SwapInt(arr + i, arr + j);
        }
    }
    SwapInt(arr + i + 1, arr + right);
    
    return (i + 1);
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