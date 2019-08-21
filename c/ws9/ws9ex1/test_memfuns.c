#include <stdio.h>
#include <string.h>

#include "memfuncs.h"

#define ARR_SIZE 50

int main()
{
	int c = 2;
	static char arr[ARR_SIZE];
	size_t n = 10;
	int i = 0;

	for (i = 0; i < ARR_SIZE; i++)
	{
		arr[i] = 1;
	}

	Memset(arr+6, c, n * sizeof(char));

	for (i = 0; i < ARR_SIZE; i++)
	{
			printf("arr[%d] = %d\n", i, arr[i]);
	}

	return (0);
}	
