#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#include "sorting.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"

#define ARR_SIZE 5000

void PrintArr(int *arr, size_t size);
void InitArr(int *arr, size_t size);
int* CopyArr(int *dest, int *src, size_t size);
int MinVal(int* arr, size_t size);
int MaxVal(int* arr, size_t size);
int IsEqualArr(int *arr1, int* arr2, size_t size);
void VerifyInt(int test, int expected, char test_name[]);
void TestInsertionSort(int* input, int* expected);
void TestSelectionSort(int* input, int* expected);
void TestCountingSort(int* input, int* expected);

int main()
{
    int arr1[ARR_SIZE] = {0};
    int arr1_copy[ARR_SIZE] = {0};
    int arr2_bubble[ARR_SIZE] = {0};

    srand(time(0));

    InitArr(arr1, ARR_SIZE);
    CopyArr(arr1_copy, arr1, ARR_SIZE);
    BubbleSort(arr1_copy, ARR_SIZE);
    CopyArr(arr2_bubble, arr1_copy, ARR_SIZE);

    printf("Sorting Algorithms Tests\n");
    printf("All tests compare output to BubbleSort output (using same input)\n");
    TestInsertionSort(CopyArr(arr1_copy, arr1, ARR_SIZE) ,arr2_bubble);
    TestSelectionSort(CopyArr(arr1_copy, arr1, ARR_SIZE) ,arr2_bubble);
    TestCountingSort(CopyArr(arr1_copy, arr1, ARR_SIZE) ,arr2_bubble);

    return (0);
}

void TestInsertionSort(int* input, int* expected)
{
    InsertionSort(input, ARR_SIZE);
    VerifyInt(IsEqualArr(input, expected, ARR_SIZE), 1, "INSERTION SORT");
}

void TestSelectionSort(int* input, int* expected)
{
    SelectionSort(input, ARR_SIZE);
    VerifyInt(IsEqualArr(input, expected, ARR_SIZE), 1, "SELECTION SORT"); 
}

void TestCountingSort(int* input, int* expected)
{
    int min = 0, max = 0;
    int arr_counting_dest[ARR_SIZE] = {0};
    min = MinVal (input, ARR_SIZE);
    max = MaxVal (input, ARR_SIZE);

    CountingSort(input, arr_counting_dest, ARR_SIZE, min, max);
    VerifyInt(IsEqualArr(arr_counting_dest, expected, ARR_SIZE), 1, "COUNTING SORT");    
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

void InitArr(int *arr, size_t size)
{
    size_t i = 0;
    for (i = 0; i < size; ++i)
    {
        arr[i] = rand() % (100 + 1 - 1) + 1;
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
	(printf(GRN), printf("## TEST PASS ## %s\n", test_name)) :
	(printf(RED), printf("## TEST FAIL ## %s\n", test_name)) ;
	printf(RESET);
}