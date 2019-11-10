#ifndef _SORTING_H_
#define _SORTING_H_

#include <stdlib.h>
#include <unistd.h>

typedef int(*cmp_func_t)(const void *data1, const void *data2);

void BubbleSort(int *arr, size_t size);

void InsertionSort(int *arr, size_t size);

void SelectionSort(int *arr, size_t size);

void CountingSort(int *arr, int *dest, size_t size, int min, int max);

void RadixSort(int *arr, size_t size, size_t base);

void CountingSortAnyBase(int *arr, int *dest, size_t size, size_t base, size_t shift);

void CountingSortBase2(int *arr, int *dest, size_t size, size_t base, size_t shift);

void MergeSort(int *dest, int *src, size_t size);

void QuickSort(const void *base, size_t nelem, size_t elem_size, cmp_func_t cmp_func);

void *BinSearchItr(const void *base, size_t nelem, size_t elem_size,
                    const void *requested_data, cmp_func_t cmp_func);

void *BinSearchR(const void *base, size_t nelem, size_t elem_size,
                    const void *requested_data, cmp_func_t cmp_func);

void *JumpSearchItr(const void *base, size_t nelem, size_t elem_size,
                    const void *requested_data, cmp_func_t cmp_func);

#endif