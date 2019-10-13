#include <stdio.h>

#include "sorting.h"

#define WORD sizeof(size_t)

static unsigned long* CopyArrUL(unsigned long *dest, unsigned long *src, size_t size);
static void PrintArrUL(unsigned long *arr, size_t size);
static void PrintArrX(unsigned long *arr, size_t size);
static void SwapInt(int *a, int* b);
static int *MinElem(int *arr, size_t size);
static unsigned long MaxVal(unsigned long *arr, size_t size);
static size_t CountDigits(unsigned long n);
static void SwapPtrUL(unsigned long **a, unsigned long** b);
static size_t Pow(size_t n, size_t base);
static int isPow2(unsigned long n);

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

void RadixSort(unsigned long *arr, size_t size, size_t base)
{
    size_t i = 0, n = 0, shift = 0;
    unsigned long *dest = (unsigned long*)calloc(size, sizeof(arr[0]));

    if (!isPow2(base))
    {
        printf("Base %lu (not base 2)\n", base);      
        n = CountDigits(MaxVal(arr, size));
        for (i = 0; i < n; ++i)
        {
            shift = Pow(i, base);  
            CountingSortAnyBase(arr, dest, size, base, shift);
            SwapPtrUL(&arr, &dest);
        }
    }
    else
    {
        printf("Base %lu (base 2)\n", base);         
        for (shift = 1, i = 0; shift < base; ++i)
        {
            shift <<= 1;
        }
        shift = i;
        n = sizeof(arr[0]) * WORD / shift;
        for (i = 0; i < n; ++i)
        {
            CountingSortBase2(arr, dest, size, base, shift * i);
            SwapPtrUL(&arr, &dest);
        }
    }
    CopyArrUL(dest, arr, size);
    free(dest);
}

void CountingSortAnyBase(unsigned long *arr, unsigned long *dest, size_t size, size_t base, size_t shift)
{
    size_t i = 0;
    unsigned long *count = (unsigned long*)calloc(base, sizeof(arr[0]));
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
    PrintArrUL(dest, size);

    free(count);
}

void CountingSortBase2(unsigned long *arr, unsigned long *dest, size_t size, size_t base, size_t shift)
{
    size_t i = 0;
    unsigned long *count = (unsigned long*)calloc(base, sizeof(arr[0]));
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
        --(count[(arr[size - i - 1] >> shift) & (base - 1)]);
        dest[count[(arr[size - i - 1] >> shift) & (base - 1)]] = arr[size - i - 1];
    }
    PrintArrX(dest, size);

    free(count);
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

static unsigned long MaxVal(unsigned long *arr, size_t size)
{
    size_t i = 0;
    unsigned long max = arr[0];

    for (i = 0; i < size; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return (max);
}

static size_t CountDigits(unsigned long n)
{
    size_t i = 0;
    while (n)
    {
        i++;
        n /= 10;
    }
    return (i);
}

static void SwapPtrUL(unsigned long **a, unsigned long** b)
{
    unsigned long *temp = *a;
    *a = *b;
    *b = temp;
}

static size_t Pow(size_t n, size_t base)
{
    size_t num = 1;

    while (n)
    {
        num *= base;
        n--;
    }

    return (num);
}

static int isPow2(size_t n)
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

static void PrintArrUL(unsigned long *arr, size_t size)
{
    size_t i = 0;
    for (i = 0; i < size; ++i)
    {
        printf("%lu ", arr[i]);
    }
    printf("\n");
}

static void PrintArrX(unsigned long *arr, size_t size)
{
    size_t i = 0;
    for (i = 0; i < size; ++i)
    {
        printf("0x%lX ", arr[i]);
    }
    printf("\n");
}

unsigned long* CopyArrUL(unsigned long *dest, unsigned long *src, size_t size)
{
    size_t i = 0;
    for (i = 0; i < size; ++i)
    {
        dest[i] = src[i];
    }

    return (dest);
}