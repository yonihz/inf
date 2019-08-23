#include <stdio.h>
#include <string.h>

#include "memfuncs.h"

#define ARR_SIZE 30

int main()
{
	static char arr1[ARR_SIZE];
	static char arr2[ARR_SIZE];
	static char arr1m[ARR_SIZE];
	static char arr2m[ARR_SIZE];
	/* int c = 2; */
	size_t n = 20;
	int i = 0;

	for (i = 0; i < ARR_SIZE; i++)
	{
		arr1[i] = 1;
		arr2[i] = 0;
		arr1m[i] = 1;
		arr2m[i] = 0;
	}

	/* test - memset */
	/*
	Memset(arr1+6, c, n * sizeof(char));
	memset(arr2+6, c, n * sizeof(char));

	for (i = 0; i < ARR_SIZE; i++)
	{
			printf("arr1[%d] = %d arr2[%d] = %d\n", i, arr1[i], i, arr2[i]);
	}
	*/

	/* test - memcpy */
	
	Memcpy(arr2+2,arr1+5, n * sizeof(char));
	memcpy(arr2m+2,arr1m+5, n * sizeof(char));

	for (i = 0; i < ARR_SIZE; i++)
	{
			printf("%d	%d	|	%d	%d\n", arr1[i], arr2[i], arr1m[i], arr2m[i]);
	}

	return (0);
}	
