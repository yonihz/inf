#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define ARR1_SIZE 10

void PrintArr(int *arr, size_t size);
void InitArr(int *arr, size_t size);
int* SortBinaryArr(int* arr, size_t size);

int main()
{
    int *arr1 = malloc(ARR1_SIZE * sizeof(int));
    srand(time(0));
    InitArr(arr1,ARR1_SIZE);
    PrintArr(arr1, ARR1_SIZE);
    SortBinaryArr(arr1, ARR1_SIZE);
    PrintArr(arr1, ARR1_SIZE);
    return (0);
}

int* SortBinaryArr(int* arr, size_t size)
{
    int *begin = arr;
    int *end = arr + size - 1;
    int temp = 0;

    while (begin < end)
    {
        while (*begin != 1 && begin < end)
        {
            ++begin;
        }
        while (*end != 0 && end > begin)
        {
            --end;
        }
        temp = *begin;
        *begin = *end;
        *end = temp;
    }
    return arr;
}

void InitArr(int *arr, size_t size)
{
    size_t i = 0;
    for (i = 0; i < size; ++i)
    {
        arr[i] = rand() % 2;
    }
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
