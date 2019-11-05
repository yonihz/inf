#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#include "sorting.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"

#define ARR_SIZE 10000

void PrintArr(int *arr, size_t size);
void PrintArrX(long unsigned int *arr, size_t size);
void InitArr(int *arr, size_t size);
int* CopyArr(int *dest, int *src, size_t size);
int IsEqualArr(int *arr1, int* arr2, size_t size);
int MinVal(int* arr, size_t size);
int MaxVal(int* arr, size_t size);
int intcmp(const void* data1, const void* data2);
void VerifyInt(int test, int expected, char test_name[]);

void TestBubbleSort(int* input, int* expected);
void TestInsertionSort(int* input, int* expected);
void TestSelectionSort(int* input, int* expected);
void TestCountingSort(int* input, int* expected);
void TestRadixSort10(int* input, int* expected);
void TestRadixSort2(int* input, int* expected);
void TestMergeSort(int *input, int *expected);

int main()
{
    int arr1[ARR_SIZE] = {0};
    int arr1_copy[ARR_SIZE] = {0};
    int arr1_qsort[ARR_SIZE] = {0};
    clock_t clock_start = 0;
    clock_t clock_end = 0;
    double nclocks = 0;

    srand(time(0));

    InitArr(arr1, ARR_SIZE);
    CopyArr(arr1_copy, arr1, ARR_SIZE);
    clock_start = clock();  
    qsort(arr1_copy, ARR_SIZE, sizeof(int), intcmp);
    clock_end = clock();
    nclocks = clock_end - clock_start;
    CopyArr(arr1_qsort, arr1_copy, ARR_SIZE);

    printf("QSORT (%f seconds)\n", nclocks/CLOCKS_PER_SEC);
    TestBubbleSort(CopyArr(arr1_copy, arr1, ARR_SIZE) ,arr1_qsort);
    TestInsertionSort(CopyArr(arr1_copy, arr1, ARR_SIZE) ,arr1_qsort);
    TestSelectionSort(CopyArr(arr1_copy, arr1, ARR_SIZE) ,arr1_qsort);
    TestCountingSort(CopyArr(arr1_copy, arr1, ARR_SIZE) ,arr1_qsort);
    TestRadixSort10(CopyArr(arr1_copy, arr1, ARR_SIZE), arr1_qsort);
    TestRadixSort2(CopyArr(arr1_copy, arr1, ARR_SIZE), arr1_qsort);
    TestMergeSort(CopyArr(arr1_copy, arr1, ARR_SIZE), arr1_qsort);

    return (0);
}

void TestBubbleSort(int* input, int* expected)
{
    clock_t clock_start = 0;
    clock_t clock_end = 0;
    double nclocks = 0;

    clock_start = clock();
    BubbleSort(input, ARR_SIZE);
    clock_end = clock();
    nclocks = clock_end - clock_start;
    VerifyInt(IsEqualArr(input, expected, ARR_SIZE), 1, "BUBBLE SORT");
    printf("(%f seconds)\n", nclocks/CLOCKS_PER_SEC);
}

void TestInsertionSort(int* input, int* expected)
{
    clock_t clock_start = 0;
    clock_t clock_end = 0;
    double nclocks = 0;

    clock_start = clock();
    InsertionSort(input, ARR_SIZE);
    clock_end = clock();
    nclocks = clock_end - clock_start;
    VerifyInt(IsEqualArr(input, expected, ARR_SIZE), 1, "INSERTION SORT");
    printf("(%f seconds)\n", nclocks/CLOCKS_PER_SEC);
}

void TestSelectionSort(int* input, int* expected)
{
    clock_t clock_start = 0;
    clock_t clock_end = 0;
    double nclocks = 0;

    clock_start = clock();
    SelectionSort(input, ARR_SIZE);
    clock_end = clock();
    nclocks = clock_end - clock_start;
    VerifyInt(IsEqualArr(input, expected, ARR_SIZE), 1, "SELECTION SORT");
    printf("(%f seconds)\n", nclocks/CLOCKS_PER_SEC);
}

void TestCountingSort(int* input, int* expected)
{
    int min = 0, max = 0;
    int arr_counting_dest[ARR_SIZE] = {0};

    clock_t clock_start = 0;
    clock_t clock_end = 0;
    double nclocks = 0;

    min = MinVal (input, ARR_SIZE);
    max = MaxVal (input, ARR_SIZE);

    clock_start = clock();
    CountingSort(input, arr_counting_dest, ARR_SIZE, min, max);
    clock_end = clock();
    nclocks = clock_end - clock_start;
    VerifyInt(IsEqualArr(arr_counting_dest, expected, ARR_SIZE), 1, "COUNTING SORT");
    printf("(%f seconds)\n", nclocks/CLOCKS_PER_SEC);
}

void TestRadixSort10(int* input, int* expected)
{
    size_t base = 10;

    clock_t clock_start = 0;
    clock_t clock_end = 0;
    double nclocks = 0;

    clock_start = clock();
    RadixSort(input, ARR_SIZE, base);
    clock_end = clock();
    nclocks = clock_end - clock_start;
    VerifyInt(IsEqualArr(input, expected, ARR_SIZE), 1, "RADIX 10 SORT");
    printf("(%f seconds)\n", nclocks/CLOCKS_PER_SEC);
}

void TestRadixSort2(int* input, int* expected)
{
    size_t base = 16;

    clock_t clock_start = 0;
    clock_t clock_end = 0;
    double nclocks = 0;

    clock_start = clock(); 
    RadixSort(input, ARR_SIZE, base);
    clock_end = clock();
    nclocks = clock_end - clock_start;
    VerifyInt(IsEqualArr(input, expected, ARR_SIZE), 1, "RADIX 2 SORT");
    printf("(%f seconds)\n", nclocks/CLOCKS_PER_SEC);
}

void TestMergeSort(int *input, int *expected)
{
    int output_mergesort[ARR_SIZE] = {0};

    clock_t clock_start = 0;
    clock_t clock_end = 0;
    double nclocks = 0;

    clock_start = clock();
    MergeSort(output_mergesort, input, ARR_SIZE);
    clock_end = clock();
    nclocks = clock_end - clock_start;
    VerifyInt(IsEqualArr(output_mergesort, expected, ARR_SIZE), 1, "MERGE SORT");  
    printf("(%f seconds)\n", nclocks/CLOCKS_PER_SEC);
}

void PrintArr(int *arr, size_t size)
{
    size_t i = 0;
    for (i = 0; i < size; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void PrintArrX(long unsigned int *arr, size_t size)
{
    size_t i = 0;
    for (i = 0; i < size; ++i)
    {
        printf("0x%lX ", arr[i]);
    }
    printf("\n");
}

void InitArr(int *arr, size_t size)
{
    size_t i = 0;
    for (i = 0; i < size; ++i)
    {
        arr[i] = rand() % (1000 + 1 - 1) + 1;
    }
}

int* CopyArr(int *dest, int *src, size_t size)
{
    size_t i = 0;
    for (i = 0; i < size; ++i)
    {
        dest[i] = src[i];
    }

    return (dest);
}

int MinVal(int* arr, size_t size)
{
    size_t i = 0;
    int min = arr[0];

    for (i = 0; i < size; i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }

    return min;
}

int MaxVal(int* arr, size_t size)
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

    return max;
}

int IsEqualArr(int *arr1, int* arr2, size_t size)
{
    size_t i = 0;

    for (i = 0; i < size; i++)
    {
        if (arr1[i] != arr2[i])
        {
            return (0);
        }
    }
    return (1);
}

void VerifyInt(int test, int expected, char test_name[])
{
	(test == expected) ?
	(printf(GRN), printf("## TEST PASS ## %s ", test_name)) :
	(printf(RED), printf("## TEST FAIL ## %s ", test_name)) ;
	printf(RESET);
}

int intcmp(const void* data1, const void* data2)
{
	return (*(int*)data1 - *(int*)data2);
}