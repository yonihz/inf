#include <stddef.h>
#include <stdio.h>

#define HOURS_IN_DAY 24
#define SIZE_ARRIVALS 5

void FindBusiest(int *arrivals, int *departures, int *busy, size_t size);
void MaxElements(int *arr, size_t size);
void PrintArr(int *arr, size_t size);

int main()
{
    /*
    int arrivals[5] = {1, 2, 9, 5, 5};
    int departures[5] = {4, 5, 12, 9, 12};
    */
    int arrivals[5] = {1, 2, 9, 23, 20};
    int departures[5] = {4, 5, 12, 3, 1};
    int busy[24] = {0};

    FindBusiest(arrivals, departures, busy, SIZE_ARRIVALS);
    PrintArr(busy, HOURS_IN_DAY);

    return (0);
}

void FindBusiest(int *arrivals, int *departures, int *busy, size_t size)
{
    size_t i = 0, j = 0;

    for (i = 0; i < HOURS_IN_DAY; i++)
    {
        busy[i] = 0;
    }

    for (i = 0; i < size; i++)
    {
        for (j = (size_t)arrivals[i]; j != (size_t)departures[i]; j++)
        {
            j = j % HOURS_IN_DAY;
            busy[j] += 1;
        }
    }

    MaxElements(busy, HOURS_IN_DAY);
}

void MaxElements(int *arr, size_t size)
{
    size_t i = 0;
    int max = 0;

    for (i = 0; i < size; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }

    for (i = 0; i < size; i++)
    {
        if (arr[i] == max)
        {
            arr[i] = 1;
        }
        else
        {
            arr[i] = 0;
        }
    }
}

void PrintArr(int *arr, size_t size)
{
    size_t i = 0;

    for (i = 0; i < size; i++)
    {
        printf("%lu\t", i);
    }
    printf("\n");

    for (i = 0; i < size; i++)
    {
        printf("%d\t", arr[i]);
    }
    printf("\n");
    
}
