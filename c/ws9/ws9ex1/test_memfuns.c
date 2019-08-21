#include <stdio.h>
#include <string.h>

#include "memfuncs.h"

#define ARR_SIZE 30

int main()
{
	static char arr1[ARR_SIZE];
	static char arr2[ARR_SIZE];
	int c = 2;
	size_t n = 21;
	int i = 0;

	for (i = 0; i < ARR_SIZE; i++)
	{
		arr1[i] = 1;
		arr2[i] = 1;
	}

	Memset(arr1+6, c, n * sizeof(char));
	memset(arr2+6, c, n * sizeof(char));

	for (i = 0; i < ARR_SIZE; i++)
	{
			printf("arr1[%d] = %d arr2[%d] = %d\n", i, arr1[i], i, arr2[i]);
	}

	return (0);
}	
