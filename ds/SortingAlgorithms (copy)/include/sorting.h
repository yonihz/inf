#ifndef _SORTING_H_
#define _SORTING_H_

#include <stddef.h>
#include <stdlib.h>

void BubbleSort(int *arr, size_t size);

void InsertionSort(int *arr, size_t size);

void SelectionSort(int *arr, size_t size);

void CountingSort(int *arr, int *dest, size_t size, int min, int max);

void RadixSort(unsigned long *arr, size_t size, size_t base);

void CountingSortAnyBase(unsigned long *arr, unsigned long *dest, size_t size, size_t base, size_t shift);

void CountingSortBase2(unsigned long *arr, unsigned long *dest, size_t size, size_t base, size_t shift);

#endif