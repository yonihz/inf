/****************************************************************
* 																*
* FILE NAME: stack_test.c										*
* 																*
* PURPOSE: Testing stack functions								*
*                                                               *
* VERSION: 0.1													*
* 																*
* DATE: 29.08.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
* Reviewer: N/A													*
* 																*
****************************************************************/

#include <stdio.h>	/* printf */
#include <string.h>	/* strcmp */

#include "vector.h"

/* colors for test results */

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"

/* debug test functions */

#ifndef NDEBUG
void TestVectorInvalidPtr();
#endif

/* API test functions */

void TestVectorCreate();

int main()
{
	TestVectorCreate();

#ifndef NDEBUG
/*	TestVectorInvalidPtr(); */
#endif
    
	return (0);
}

/* verify functions - compare to expected value and print pass/fail */

void VerifyVectort(vector_t* test, vector_t* expected, char test_name[])
{
	(test == expected) ?
	(printf(GRN), printf("%s # TEST PASS #\n", test_name)) :
	(printf(RED), printf("%s # TEST FAIL #\n", test_name)) ;
	printf(RESET);
}

void VerifyInt(int test, int expected, char test_name[])
{
	(test == expected) ?
	(printf(GRN), printf("%s # TEST PASS #\n", test_name)) :
	(printf(RED), printf("%s # TEST FAIL #\n", test_name)) ;
	printf(RESET);
}

void VerifySizet(size_t test,size_t expected, char test_name[])
{
	(test == expected) ?
	(printf(GRN), printf("%s # TEST PASS #\n", test_name)) :
	(printf(RED), printf("%s # TEST FAIL #\n", test_name)) ;
	printf(RESET);
}

void VerifyVoidptr(void* test, void* expected, char test_name[])
{
	if (NULL == expected)
	{
		(test == NULL) ?
		(printf(GRN), printf("%s # TEST PASS #\n", test_name)) :
		(printf(RED), printf("%s # TEST FAIL #\n", test_name)) ;
		return;
	}

	(*(int*)test == *(int*)expected) ?
	(printf(GRN), printf("%s # TEST PASS #\n", test_name)) :
	(printf(RED), printf("%s # TEST FAIL #\n", test_name)) ;
	printf(RESET);
}

void VerifyChar(char test[], char expected[], char test_name[])
{
	(!strcmp(test, expected)) ?
	(printf(GRN), printf("%s # TEST PASS #\n", test_name)) :
	(printf(RED), printf("%s # TEST FAIL #\n", test_name)) ;
	printf(RESET);
}

/* Test functions for API */

void TestVectorCreate()
{
	vector_t* vector1 = NULL;
    size_t num_of_elements = 5;
    size_t size_of_elements = sizeof(int);
    int a[5] = {0, 1, 2, 3, 4};

	printf("VectorCreate Tests\n");
    vector1 = VectorCreate(num_of_elements, size_of_elements);

    VerifyInt(VectorPushBack(vector1, (a+3)), 1,
    "TEST 1 - VECTOR CREATE AND PUSH");

	VectorDestroy(vector1);
}

/* Test functions for debug version */

#ifndef NDEBUG

void TestVectorInvalidPtr()
{

}
#endif
