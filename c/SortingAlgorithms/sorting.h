#ifndef _SORTING_H_
#define _SORTING_H_

#include <stdlib.h>
#include <unistd.h>

void BubbleSort(int *arr, size_t size);

void InsertionSort(int *arr, size_t size);

void SelectionSort(int *arr, size_t size);

void CountingSort(int *arr, int *dest, size_t size, int min, int max);

void RadixSort(int *arr, size_t size, size_t base);

void CountingSortAnyBase(int *arr, int *dest, size_t size, size_t base, size_t shift);

void CountingSortBase2(int *arr, int *dest, size_t size, size_t base, size_t shift);

void MergeSort(int *dest, int *src, size_t size);

void QuickSort(int *arr, ssize_t left, ssize_t right);

#endif