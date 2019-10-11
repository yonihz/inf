/****************************************************************
* 																*
* FILE NAME: vector_test.c										*
* 																*
* PURPOSE: Testing vector functions								*
* 																*
* DATE: 29.08.19												*
* 																*
* Author: Yoni Horovitz											*
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
void TestVectorSize0();
#endif

/* API test functions */

static void TestVectorCreate();
static void TestVectorGrow();
static void TestVectorGetItem();
static void TestVectorReserve();

int main()
{
	TestVectorCreate();
	TestVectorGrow();
	TestVectorGetItem();
	TestVectorReserve();

#ifndef NDEBUG
/*	TestVectorInvalidPtr(); */  
/*	TestVectorSize0(); */ 
#endif
    
	return (0);
}

/* verify functions - compare to expected value and print pass/fail */

void VerifyVectort(vector_t* test, vector_t* expected, char test_name[])
{
	(test == expected) ?
	(printf(GRN), printf("## TEST PASS ## %s\n", test_name)) :
	(printf(RED), printf("## TEST FAIL ## %s\n", test_name)) ;
	printf(RESET);
}

void VerifyInt(int test, int expected, char test_name[])
{
	(test == expected) ?
	(printf(GRN), printf("## TEST PASS ## %s\n", test_name)) :
	(printf(RED), printf("## TEST FAIL ## %s\n", test_name)) ;
	printf(RESET);
}

void VerifySizet(size_t test,size_t expected, char test_name[])
{
	(test == expected) ?
	(printf(GRN), printf("## TEST PASS ## %s\n", test_name)) :
	(printf(RED), printf("## TEST FAIL ## %s\n", test_name)) ;
	printf(RESET);
}

void VerifyVoidptr(void* test, void* expected, char test_name[])
{
	if (NULL == expected)
	{
		(test == NULL) ?
		(printf(GRN), printf("## TEST PASS ## %s\n", test_name)) :
		(printf(RED), printf("## TEST FAIL ## %s\n", test_name)) ;
		printf(RESET);
		return;
	}

	(*(int*)test == *(int*)expected) ?
	(printf(GRN), printf("## TEST PASS ## %s\n", test_name)) :
	(printf(RED), printf("## TEST FAIL ## %s\n", test_name)) ;
	printf(RESET);
}

void VerifyChar(char test[], char expected[], char test_name[])
{
	(!strcmp(test, expected)) ?
	(printf(GRN), printf("## TEST PASS ## %s\n", test_name)) :
	(printf(RED), printf("## TEST FAIL ## %s\n", test_name)) ;
	printf(RESET);
}

/* Test functions for API */

void TestVectorCreate()
{
	vector_t* vector1 = NULL;
    size_t num_of_elements = 8;
    size_t size_of_element = sizeof(int);
    int a[8] = {0, 1, 2, 3, 4, 5, 6, 7};

	printf("VectorCreate Tests\n");
    vector1 = VectorCreate(size_of_element, num_of_elements);

    VerifyInt(VectorPushBack(vector1, (a+3)), 0,
    "TEST 1 - VECTOR CREATE AND PUSH");

	VectorDestroy(vector1);
}

void TestVectorGrow()
{
	vector_t* vector1 = NULL;
    size_t num_of_elements = 4;
    size_t size_of_element = sizeof(int);
    int a[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

	printf("Grow and Shrink Tests\n");
    vector1 = VectorCreate(size_of_element, num_of_elements);

    VerifySizet(VectorCapacity(vector1), 4,
    "TEST 1 - CAPACITY IS 4 AFTER CREATE WITH 4 ELEMENTS");

	VectorPushBack(vector1, (a+0));
	VectorPushBack(vector1, (a+1));
	VectorPushBack(vector1, (a+2));
	VectorPushBack(vector1, (a+3));

    VerifySizet(VectorCapacity(vector1), 4,
    "TEST 1 - CAPACITYIS 4 AFTER 4 PUSH");
    VerifySizet(VectorSize(vector1), 4,
    "TEST 2 - SIZE IS 4 AFTER 4 PUSH");

	VectorPushBack(vector1, (a+4));

    VerifySizet(VectorCapacity(vector1), 8,
    "TEST 3 - CAPACITY IS 8 AFTER 5 PUSH");

    VerifySizet(VectorSize(vector1), 5,
    "TEST 4 - SIZE IS 5 AFTER 5 PUSH");

	VectorPushBack(vector1, (a+5));
	VectorPushBack(vector1, (a+6));
	VectorPushBack(vector1, (a+7));
	VectorPushBack(vector1, (a+8));

    VerifySizet(VectorCapacity(vector1), 16,
    "TEST 5 - CAPACITY IS 16 AFTER 9 PUSH");

    VerifySizet(VectorSize(vector1), 9,
    "TEST 6 - SIZE IS 9 AFTER 9 PUSH");

	VectorPopBack(vector1);
	VectorPopBack(vector1);
	VectorPopBack(vector1);
	VectorPopBack(vector1);

    VerifySizet(VectorCapacity(vector1), 16,
    "TEST 7 - CAPACITY IS 16 AFTER 4 POP");

    VerifySizet(VectorSize(vector1), 5,
    "TEST 8 - SIZE IS 5 AFTER 4 PUSH");

	VectorPopBack(vector1);

    VerifySizet(VectorCapacity(vector1), 8,
    "TEST 9 - CAPACITY IS 8 AFTER 1 POP");

    VerifySizet(VectorSize(vector1), 4,
    "TEST 10 - SIZE IS 4 AFTER 1 POP");

	VectorPopBack(vector1);

    VerifySizet(VectorCapacity(vector1), 8,
    "TEST 11 - CAPACITY IS 8 AFTER 1 POP");

    VerifySizet(VectorSize(vector1), 3,
    "TEST 12 - SIZE IS 3 AFTER 1 POP");

	VectorPopBack(vector1);

    VerifySizet(VectorCapacity(vector1), 4,
    "TEST 13 - CAPACITY IS 4 AFTER 1 POP");

    VerifySizet(VectorSize(vector1), 2,
    "TEST 14 - SIZE IS 2 AFTER 1 POP");

	VectorPopBack(vector1);

    VerifySizet(VectorCapacity(vector1), 2,
    "TEST 15 - CAPACITY IS 2 AFTER 1 POP");

    VerifySizet(VectorSize(vector1), 1,
    "TEST 16 - SIZE IS 1 AFTER 1 POP");

	VectorPopBack(vector1);

    VerifySizet(VectorCapacity(vector1), 2,
    "TEST 17 - CAPACITY IS 2 AFTER 1 POP");

    VerifySizet(VectorSize(vector1), 0,
    "TEST 18 - SIZE IS 0 AFTER 1 POP");

	VectorPopBack(vector1);

    VerifySizet(VectorCapacity(vector1), 2,
    "TEST 19 - CAPACITY IS 2 AFTER 1 POP");

    VerifySizet(VectorSize(vector1), 0,
    "TEST 20 - SIZE IS 0 AFTER 1 POP");

	VectorDestroy(vector1);
}

void TestVectorGetItem()
{
	vector_t* vector1 = NULL;
    size_t num_of_elements = 4;
    size_t size_of_element = sizeof(int);
    int a[8] = {0, 1, 2, 3, 4, 5, 6, 7};

	printf("Push Pop GetItem Tests\n");
    vector1 = VectorCreate(size_of_element, num_of_elements);

    VerifyVoidptr(VectorGetItemAddress(vector1, 0), NULL,
    "TEST 1 - GET ITEM IS NULL AFTER CREATE");

	VectorPushBack(vector1, (a+0));
	VectorPushBack(vector1, (a+1));
	VectorPushBack(vector1, (a+2));
	VectorPushBack(vector1, (a+3));
	VectorPushBack(vector1, (a+4));

    VerifyVoidptr(VectorGetItemAddress(vector1, 0), (a+0),
    "TEST 2 - GET ITEM 0 AFTER 5 PUSH");
    VerifyVoidptr(VectorGetItemAddress(vector1, 1), (a+1),
    "TEST 3 - GET ITEM 1 AFTER 5 PUSH");
    VerifyVoidptr(VectorGetItemAddress(vector1, 2), (a+2),
    "TEST 4 - GET ITEM 2 AFTER 5 PUSH");
    VerifyVoidptr(VectorGetItemAddress(vector1, 3), (a+3),
    "TEST 5 - GET ITEM 3 AFTER 5 PUSH");
    VerifyVoidptr(VectorGetItemAddress(vector1, 4), (a+4),
    "TEST 6 - GET ITEM 4 AFTER 5 PUSH");

    VerifyVoidptr(VectorGetItemAddress(vector1, 5), NULL,
    "TEST 7 - GET ITEM OUT OF RANGE AFTER 5 PUSH");

	VectorPopBack(vector1);
	VectorPopBack(vector1);
	VectorPopBack(vector1);
	VectorPopBack(vector1);

    VerifyVoidptr(VectorGetItemAddress(vector1, 0), (a+0),
    "TEST 8 - GET ITEM 0 AFTER 5 PUSH");

	VectorPopBack(vector1);

    VerifyVoidptr(VectorGetItemAddress(vector1, 0), NULL,
    "TEST 9 - GET ITEM 0 AFTER VECTOR IS EMPTY");

	VectorDestroy(vector1);
}

void TestVectorReserve()
{
	vector_t* vector1 = NULL;
    size_t num_of_elements = 4;
    size_t size_of_element = sizeof(int);
    int a[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

	printf("Reserve Tests\n");
    vector1 = VectorCreate(size_of_element, num_of_elements);

    VerifySizet(VectorCapacity(vector1), 4,
    "TEST 1 - CAPACITY IS 4 AFTER CREATE WITH 4 ELEMENTS");

	VectorReserve(vector1, 6);

    VerifySizet(VectorCapacity(vector1), 6,
    "TEST 2 - CAPACITY IS 6 AFTER RESERVE WITH 6 ELEMENTS");

	VectorPushBack(vector1, (a+0));
	VectorPushBack(vector1, (a+1));
	VectorPushBack(vector1, (a+2));
	VectorPushBack(vector1, (a+3));
	VectorPushBack(vector1, (a+4));
	VectorPushBack(vector1, (a+5));
	VectorPushBack(vector1, (a+6));

    VerifySizet(VectorCapacity(vector1), 12,
    "TEST 3 - CAPACITY IS 12 AFTER 7 PUSH");

	VectorReserve(vector1, 14);

    VerifySizet(VectorCapacity(vector1), 14,
    "TEST 4 - CAPACITY IS 14 AFTER RESERVE WITH 14 ELEMENTS");

	VectorPopBack(vector1);
	VectorPopBack(vector1);
	VectorPopBack(vector1);

    VerifySizet(VectorCapacity(vector1), 14,
    "TEST 5 - CAPACITY IS 14 AFTER 3 POP");

	VectorReserve(vector1, 12);

    VerifySizet(VectorCapacity(vector1), 12,
    "TEST 2 - CAPACITY IS 12 AFTER RESERVE WITH 12 ELEMENTS");

	VectorDestroy(vector1);
}

/* Test functions for debug version */

#ifndef NDEBUG

void TestVectorInvalidPtr()
{
	vector_t* vector1 = NULL;
    size_t num_of_elements = 4;
    size_t size_of_element = sizeof(int);
    int a[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

	printf("VectorDestroy Debug Tests - INVALID POINTER\n");
    vector1 = VectorCreate(size_of_element, num_of_elements);
	VectorPushBack(vector1, (a+0));

	VectorDestroy(vector1);
	VectorDestroy(vector1);
}

void TestVectorSize0()
{
	vector_t* vector1 = NULL;
    size_t size_of_element = sizeof(int);
    int a[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

	printf("VectorCreate Debug Tests - SIZE 0 AND PUSH\n");
    vector1 = VectorCreate(size_of_element, 0);
	VectorPushBack(vector1, (a+0));
}
#endif
