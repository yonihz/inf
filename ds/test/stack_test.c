/****************************************************************
* 																*
* FILE NAME: stack_test.c										*
* 																*
* PURPOSE: Testing stack functions								*
* 																*
* DATE: 29.08.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
****************************************************************/

#include <stdio.h>	/* printf */

#include "stack.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"

#ifndef NDEBUG
void TestStackCreateSizeMax();
void TestStackCreateSize0();
void TestStackInvalidPtr();
#endif

void TestStackCreateAndPush();
void TestStackPush();
void TestStackPop();
void TestStackPeek();
void TestStackSize();
void TestStackIsEmpty();
void TestStackLIFO();

int main()
{
	TestStackCreateAndPush();
    TestStackPush();
    TestStackPop();
    TestStackPeek();
    TestStackSize();
    TestStackIsEmpty();
    TestStackLIFO();

#ifndef NDEBUG
/*	TestStackCreateSize0(); */
/*	TestStackInvalidPtr(); */
/*	TestStackCreateSizeMax(); */
#endif
    
	return (0);
}

void VerifyStackt(stack_t* test, stack_t* expected, char pass[], char fail[])
{
	(test == expected) ?
	(printf(GRN), printf("%s\n", pass)) :
	(printf(RED), printf("%s\n", fail)) ;
	printf(RESET);
}

void VerifyInt(int test, int expected, char pass[], char fail[])
{
	(test == expected) ?
	(printf(GRN), printf("%s\n", pass)) :
	(printf(RED), printf("%s\n", fail)) ;
	printf(RESET);
}

void VerifySizet(size_t test,size_t expected, char pass[], char fail[])
{
	(test == expected) ?
	(printf(GRN), printf("%s\n", pass)) :
	(printf(RED), printf("%s\n", fail)) ;
	printf(RESET);
}

void VerifyVoidptr(void* test, void* expected, char pass[], char fail[])
{
	if (NULL == expected)
	{
		(test == NULL) ?
		(printf(GRN), printf("%s\n", pass)) :
		(printf(RED), printf("%s\n", fail)) ;
		return;
	}

	(*(int*)test == *(int*)expected) ?
	(printf(GRN), printf("%s\n", pass)) :
	(printf(RED), printf("%s\n", fail)) ;
	printf(RESET);
}

void TestStackCreateAndPush()
{
	stack_t* stack1 = NULL;
    size_t num_of_elements = 5;
    size_t size_of_elements = sizeof(int);
    int a[5] = {0, 1, 2, 3, 4};

	printf("StackCreate Tests\n");
    stack1 = StackCreate(num_of_elements, size_of_elements);

    VerifyInt(StackPush(stack1, (a+3)), 1,
    "TEST 1 PASSED - CREATE AND PUSH",
    "TEST 1 FAILED - CREATE AND PUSH");

	StackDestroy(stack1);
	stack1 = NULL;
}

void TestStackPush()
{
	stack_t* stack1 = NULL;
    size_t num_of_elements = 5;
    size_t size_of_elements = sizeof(int);
    int a[5] = {0, 1, 2, 3, 4};

	printf("StackPush Tests\n");
    stack1 = StackCreate(num_of_elements, size_of_elements);

    StackPush(stack1, (a+0));
    StackPush(stack1, (a+1));
    StackPush(stack1, (a+2));

    VerifyInt(StackPush(stack1, (a+3)), 1,
    "TEST 1 PASSED - PUSH SUCCESS",
    "TEST 1 FAILED - PUSH SUCCESS");

    StackPush(stack1, (a+4));

    VerifyInt(StackPush(stack1, (a+4)), 0,
    "TEST 2 PASSED - PUSH TO FULL STACK",
    "TEST 2 FAILED - PUSH TO FULL STACK");

	StackDestroy(stack1);
	stack1 = NULL;
}

void TestStackPop()
{
    stack_t* stack1 = NULL;
    size_t num_of_elements = 5;
    size_t size_of_elements = sizeof(int);
    int a[5] = {0, 1, 2, 3, 4};

	printf("StackPop Tests\n");	
    stack1 = StackCreate(num_of_elements, size_of_elements);
	StackPop(stack1);

    VerifySizet(StackSize(stack1), 0ul,
    "TEST 1 PASSED - POP AFTER CREATE",
    "TEST 1 FAILED - POP AFTER CREATE");

    StackPush(stack1, (a+0));
    StackPush(stack1, (a+1));
	StackPop(stack1);
	StackPop(stack1);
	StackPop(stack1);

    VerifySizet(StackSize(stack1), 0ul,
    "TEST 2 PASSED - POP AFTER STACK IS EMPTY",
    "TEST 2 FAILED - POP AFTER STACK IS EMPTY");

	StackDestroy(stack1);
	stack1 = NULL;
}

void TestStackPeek()
{
    stack_t* stack1 = NULL;
    size_t num_of_elements = 5;
    size_t size_of_elements = sizeof(int);
    int a[5] = {0, 1, 2, 3, 4};

	printf("StackPeek Tests\n");	
    stack1 = StackCreate(num_of_elements, size_of_elements);

    VerifyVoidptr((void*)StackPeek(stack1), NULL,
    "TEST 1 PASSED - EMPTY",
    "TEST 1 FAILED - EMPTY");

    StackPush(stack1, (a+0));
    StackPush(stack1, (a+1));

    VerifyVoidptr((void*)StackPeek(stack1),(a+1),
    "TEST 2 PASSED - PEEK AFTER PUSH",
    "TEST 2 FAILED - PEEK AFTER PUSH");

	StackDestroy(stack1);
	stack1 = NULL;
}

void TestStackSize()
{
	stack_t* stack1 = NULL;
    size_t num_of_elements = 5;
    size_t size_of_elements = sizeof(int);
    int a[5] = {0, 1, 2, 3, 4};

	printf("StackSize Tests\n");
    stack1 = StackCreate(num_of_elements, size_of_elements);
    VerifySizet(StackSize(stack1), 0ul,
    "TEST 1 PASSED - EMPTY STACK AFTER CREATE",
    "TEST 1 FAILED - EMPTY STACK AFTER CREATE");

    StackPush(stack1, (a+0));
    StackPush(stack1, (a+1));
    StackPush(stack1, (a+2));

    VerifySizet(StackSize(stack1), 3ul,
    "TEST 2 PASSED - SIZE AFTER 3 PUSH",
    "TEST 2 FAILED - SIZE AFTER 3 PUSH");

	StackPop(stack1);

    VerifySizet(StackSize(stack1), 2ul,
    "TEST 3 PASSED - SIZE AFTER 1 POP",
    "TEST 3 FAILED - SIZE AFTER 1 POP");

	StackPop(stack1);
	StackPop(stack1);

    VerifySizet(StackSize(stack1), 0ul,
    "TEST 4 PASSED - EMPTY STACK AFTER 2 POP",
    "TEST 4 FAILED - EMPTY STACK AFTER 2 POP");

	StackDestroy(stack1);
	stack1 = NULL;
}

void TestStackIsEmpty()
{
	stack_t* stack1 = NULL;
    size_t num_of_elements = 5;
    size_t size_of_elements = sizeof(int);
    int a[5] = {0, 1, 2, 3, 4};

	printf("StackIsEmpty Tests\n");
    stack1 = StackCreate(num_of_elements, size_of_elements);

    VerifyInt(StackIsEmpty(stack1), 1,
    "TEST 1 PASSED - EMPTY STACK AFTER CREATE",
    "TEST 1 FAILED - EMPTY STACK AFTER CREATE");

    StackPush(stack1, (a+0));
    StackPush(stack1, (a+1));
    StackPush(stack1, (a+2));

    VerifyInt(StackIsEmpty(stack1), 0,
    "TEST 2 PASSED - NON-EMPTY STACK AFTER PUSH",
    "TEST 2 FAILED - NON-EMPTY STACK AFTER PUSH");

	StackDestroy(stack1);
	stack1 = NULL;
}

void TestStackLIFO()
{
    stack_t* stack1 = NULL;
    size_t num_of_elements = 5;
    size_t size_of_elements = sizeof(int);
    int a[5] = {0, 1, 2, 3, 4};

	printf("LIFO Tests\n");
    stack1 = StackCreate(num_of_elements, size_of_elements);
    StackPush(stack1, (a+0));
    VerifyVoidptr((void*)StackPeek(stack1),(a+0),
    "TEST 1 PASSED - PUSH AND PEEK",
    "TEST 1 FAILED - PUSH AND PEEK");

    StackPush(stack1, (a+1));
    VerifyVoidptr((void*)StackPeek(stack1),(a+1),
    "TEST 2 PASSED - PUSH AND PEEK",
    "TEST 2 FAILED - PUSH AND PEEK");

    StackPush(stack1, (a+2));
    VerifyVoidptr((void*)StackPeek(stack1),(a+2),
    "TEST 3 PASSED - PUSH AND PEEK",
    "TEST 3 FAILED - PUSH AND PEEK");

    StackPop(stack1);
    VerifyVoidptr((void*)StackPeek(stack1),(a+1),
    "TEST 4 PASSED - POP AND PEEK",
    "TEST 4 FAILED - POP AND PEEK");

    StackPop(stack1);
    VerifyVoidptr((void*)StackPeek(stack1),(a+0),
    "TEST 5 PASSED - POP AND PEEK",
    "TEST 5 FAILED - POP AND PEEK");

	StackDestroy(stack1);
	stack1 = NULL;
}

#ifndef NDEBUG
void TestStackCreateSizeMax()
{
	printf("StackCreate Debug Test - SIZE MAX\n");
    StackCreate(~0ul, ~0ul);
}

void TestStackCreateSize0()
{
	printf("StackCreate Debug Test - SIZE 0\n");
    StackCreate(0, 1ul);
}

void TestStackInvalidPtr()
{
	stack_t* stack1 = NULL;
    size_t num_of_elements = 5;
    size_t size_of_elements = sizeof(int);

	printf("StackDestroy Debug Test - INVALID POINTER\n");
    stack1 = StackCreate(num_of_elements, size_of_elements);

	StackDestroy(stack1);
	StackDestroy(stack1);
}
#endif
