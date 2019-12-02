#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

#define ARR_SIZE 100000

size_t *arr;

void *AssignToArr(void *idx_ptr);

int main()
{
    size_t i = 0;
    int is_check_fail = 0;
    pthread_t pthread_arr[ARR_SIZE];
    
    arr = (size_t*)calloc(ARR_SIZE, sizeof(arr[0]));

    /* solution with detach */
    for (i = 0; i < ARR_SIZE; i++)
    {
        pthread_create(&(pthread_arr[i]), NULL, &AssignToArr, &i);
        pthread_detach(pthread_arr[i]);
    }

    /* solution with create all and then join all: fails after 32754 threads */
    /*
    for (i = 0; i < ARR_SIZE; i++)
    {
        if (pthread_create(&(pthread_arr[i]), NULL, &AssignToArr, &i))
        {
            printf("failed: thread number %lu\n", i);
            exit(1);
        }
    }
    */

    for (i = 0; i < ARR_SIZE; i++)
    {
        pthread_join(pthread_arr[i], NULL);
    }
    */

    /* solution with create and join (not parallel) */
    /*
    for (i = 0; i < ARR_SIZE; i++)
    {
        pthread_create(&(pthread_arr[i]), NULL, &AssignToArr, &i);
        pthread_join(pthread_arr[i], NULL);
    }
    */

    sleep(10);

    for (i = 0; i < ARR_SIZE && !is_check_fail; i++)
    {
        if (arr[i] != i + 1)
        {
            break;
        }
    }

    if (is_check_fail)
    {
        printf("Failed\n");
    }
    else
    {
        printf("Success\n");
    }
    
    return (0);
}

void *AssignToArr(void *idx_ptr)
{
    size_t i = *(size_t*)idx_ptr;
    arr[i] = i + 1;

    return (NULL);
}