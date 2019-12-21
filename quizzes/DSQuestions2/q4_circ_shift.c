#include <stdio.h>
#include <stdlib.h>

#define ARR_SIZE 10

void CShift(char *arr, size_t size, size_t shift);
void ReverseArr(char *arr, size_t size);
void PrintArr(char *arr, size_t size);

int main()
{
    char arr[ARR_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t shift = 3;

    printf("Shift array by %lu:\n", shift);
    CShift(arr, ARR_SIZE, shift);
    PrintArr(arr, ARR_SIZE);

    return 0;
}

void CShift(char *arr, size_t size, size_t shift)
{
    shift = shift % size;
    ReverseArr(arr, size);
    ReverseArr(arr, shift);
    ReverseArr(arr + shift, size - shift);
}

void ReverseArr(char *arr, size_t size)
{
    size_t i = 0;
    char temp = 0;

    for (i = 0; i < (size / 2); ++i)
    {
        temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}

void PrintArr(char *arr, size_t size)
{
    size_t i = 0;
    
    for (i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
}