#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "poly.h"

#define ARR_SIZE 5

int main()
{
	data_t* my_arr = NULL;

	int my_int = 17;
	float my_float = 3.14;
	char* my_str = "Hello world";
	data_type_t type1 = 0;
	
	my_arr = calloc(sizeof(data_t), ARR_SIZE);

	/* test1: set int, print, add, print again */

	printf("\n\ntest1: int\n");
	PolySetValue(&my_arr[1], TYPE_INT, &my_int);
	PolyPrintSingle(&my_arr[1]);
	PolyAdd(&my_arr[1], 10);
	PolyPrintSingle(&my_arr[1]);

	/* test2: set float, print, add, print again */

	printf("\n\ntest2: float\n");
	PolySetValue(&my_arr[2], TYPE_FLT, &my_float);
	PolyPrintSingle(&my_arr[2]);
	PolyAdd(&my_arr[2], 10);
	PolyPrintSingle(&my_arr[2]);

	/* test3: set string, print, add, print again */

	printf("\n\ntest3: string\n");
	PolySetValue(&my_arr[3], TYPE_STR, my_str);
	PolyPrintSingle(&my_arr[3]);
	PolyAdd(&my_arr[3], 10);
	PolyPrintSingle(&my_arr[3]);

	/* test4: print all, gettype, clean all */

	printf("\n\ntest4: printall\n");
	PolyPrintAll(my_arr, ARR_SIZE);
	type1 = PolyGetType(&my_arr[3]);
	printf("Type is %d\n",type1);
	PolyCleanAll(my_arr, ARR_SIZE);

	free(my_arr);

	return (0);
} 
