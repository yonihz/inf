#include <stdio.h> /* for printf() */
#include <stdlib.h> /* for malloc() */
#include <string.h> /* for strlen() */
#include "poly.h"

#define ARR_SIZE 5

int main()
{
	data_t* my_arr = NULL;

	int my_int1 = 17;
	int my_int2 = 13;
	float my_float1 = 3.14;
	float my_float2 = 5.89;
	char* my_str1 = "Hello world";
	char* my_str2 = "blah";
	data_type_t type1 = 0;
	
	my_arr = calloc(sizeof(data_t), ARR_SIZE);

	if (NULL == my_arr)
	{
		printf("Error - malloc failed\n");
		exit(1);
	}

	/* test1: set int, print, add, print again */

	printf("\n\ntest1: int\n");
	PolySetValue(&my_arr[1], TYPE_INT, &my_int1);
	PolyPrintSingle(&my_arr[1]);
	PolyAdd(&my_arr[1], 10);
	PolyPrintSingle(&my_arr[1]);

	/* test2: set float, print, add, print again */

	printf("\n\ntest2: float\n");
	PolySetValue(&my_arr[2], TYPE_FLT, &my_float1);
	PolyPrintSingle(&my_arr[2]);
	PolyAdd(&my_arr[2], 10);
	PolyPrintSingle(&my_arr[2]);

	/* test3: set string, print, add, print again */

	printf("\n\ntest3: string\n");
	PolySetValue(&my_arr[3], TYPE_STR, my_str1);
	PolyPrintSingle(&my_arr[3]);
	PolyAdd(&my_arr[3], 10);
	PolyPrintSingle(&my_arr[3]);

	/* test4: set string where float was, print, add, print again */

	printf("\n\ntest4: string where float was\n");
	PolySetValue(&my_arr[2], TYPE_STR, my_str2);
	PolyPrintSingle(&my_arr[2]);
	PolyAdd(&my_arr[2], 10);
	PolyPrintSingle(&my_arr[2]);

	/* test5: set int where string was, print, add, print again */

	printf("\n\ntest5: int where string was\n");
	PolySetValue(&my_arr[3], TYPE_INT, &my_int2);
	PolyPrintSingle(&my_arr[3]);
	PolyAdd(&my_arr[3], 10);
	PolyPrintSingle(&my_arr[3]);

	/* test6: set int where string was, print, add, print again */

	printf("\n\ntest6: float where int was\n");
	PolySetValue(&my_arr[1], TYPE_FLT, &my_float2);
	PolyPrintSingle(&my_arr[1]);
	PolyAdd(&my_arr[1], 10);
	PolyPrintSingle(&my_arr[1]);

	/* test7: print all, gettype, clean all */

	printf("\n\ntest7: printall\n");
	PolyPrintAll(my_arr, ARR_SIZE);
	printf("\n\nGetType test\n");
	type1 = PolyGetType(&my_arr[3]);
	printf("Type is %d\n",type1);
	PolyCleanAll(my_arr, ARR_SIZE);

	free(my_arr);

	return (0);
} 
