#include <stdio.h>
#include <stdlib.h>

#define ARR_SIZE 10

enum {SUCCESS = 0, FAILURE = 1} status_t;

int SumOfTwo(
        unsigned int *arr,
        size_t size, 
        unsigned int *val1, 
        unsigned int *val2, 
        unsigned int sum_of_two);

int main()
{
    unsigned int arr[ARR_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    unsigned int val1 = 0, val2 = 0;
    unsigned int sum_of_two = 0;
    int status = 0;

    sum_of_two = 6;
    status = SumOfTwo(arr, ARR_SIZE, &val1, &val2, sum_of_two);
    printf("sum_of_two = %u, status = %d, val1 = %u, val2 = %u\n", sum_of_two, status, val1, val2);

    sum_of_two = 13;
    status = SumOfTwo(arr, ARR_SIZE, &val1, &val2, sum_of_two);
    printf("sum_of_two = %u, status = %d, val1 = %u, val2 = %u\n", sum_of_two, status, val1, val2);

    sum_of_two = 17;
    status = SumOfTwo(arr, ARR_SIZE, &val1, &val2, sum_of_two);
    printf("sum_of_two = %u, status = %d, val1 = %u, val2 = %u\n", sum_of_two, status, val1, val2);

    sum_of_two = 20;
    status = SumOfTwo(arr, ARR_SIZE, &val1, &val2, sum_of_two);
    printf("sum_of_two = %u, status = %d, val1 = %u, val2 = %u\n", sum_of_two, status, val1, val2);

    return 0;
}

int SumOfTwo(
        unsigned int *arr,
        size_t size, 
        unsigned int *val1, 
        unsigned int *val2, 
        unsigned int sum_of_two)
{
    size_t left = 0, right = 0;

    for (left = 0; left < size - 1; ++left)
    {
        for (right = left + 1; right < size; ++right)
        {
            if (sum_of_two == (arr[left] + arr[right]))
            {
                *val1 = arr[left];
                *val2 = arr[right];
                
                return SUCCESS;
            }
        }
    }

    *val1 = 0;
    *val2 = 0;

    return FAILURE;
}