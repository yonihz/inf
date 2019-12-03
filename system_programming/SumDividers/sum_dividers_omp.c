#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

#define MAX_THREADS 1 

size_t *psums_arr_base;
size_t sub_range;
size_t num;
size_t nthreads_ref;

size_t SumDividers(size_t n);
void *PartialSumDividers(void *psums_arr_addr);

int main()
{
    size_t sum_div = 0;
    size_t n = 100;

    sum_div = SumDividers(n);

    printf("Sum of dividers of %lu is %lu / %lu threads\n", n, sum_div, nthreads_ref);

    return (0);
}

size_t SumDividers(size_t n)
{
    size_t nthreads = 0, i = 0, sum = 0;
    size_t *psums_arr_addr = NULL;
    pthread_t *pthreads_arr = NULL;

    num = n;
    nthreads = n > MAX_THREADS ? MAX_THREADS : n;
    sub_range = n / nthreads;

    nthreads_ref = nthreads;

    psums_arr_base = (size_t*)calloc(nthreads, sizeof(size_t));
    pthreads_arr = (pthread_t*)calloc(nthreads, sizeof(pthread_t));
    
    for (i = 0; i < nthreads; i++)
    {
        psums_arr_addr = psums_arr_base + i;
        if (pthread_create((pthreads_arr + i), NULL, &PartialSumDividers, psums_arr_addr))
        {
            printf("failed: thread number %lu\n", i);
            exit(1);
        }
    }

    for (i = 0; i < nthreads; i++)
    {
        pthread_join(pthreads_arr[i], NULL);
    }

    for (i = 0; i < nthreads; i++)
    {
        sum = sum + *(psums_arr_base + i);
    }

    free(psums_arr_base);
    free(pthreads_arr);

    return (sum);
}

void *PartialSumDividers(void *psums_arr_addr)
{
    size_t i = 0, min = 0, max = 0, sum = 0;
    i = ((char*)psums_arr_addr - (char*)psums_arr_base)/sizeof(size_t);
    min = i * sub_range + 1;
    max = min + sub_range;

    #pragma omp parallel for
    for (i = min; i < max; i++)
    {
        if (0 == num % i)
        {
            sum = sum + i;
        }
    }

    *(size_t*)psums_arr_addr = sum;

    return (NULL);
}