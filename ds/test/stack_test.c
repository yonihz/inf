#include <stdio.h>
#include <string.h>
#include "stack.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"

void TestStackCreate();
void TestStackDestroy();
void TestStackPush();
void TestStackPop();
void TestStackPeek();
void TestStackSize();
void TestStackIsEmpty();
void TestStackLIFO();

int main()
{
	TestStackCreate();
    TestStackDestroy();
    TestStackPush();
    TestStackPop();
    TestStackPeek();
    TestStackSize();
    TestStackIsEmpty();
    TestStackLIFO();
    
	return (0);
}

void VerifyStackt(stack_t* test, stack_t* expected, char pass[], char fail[])
{
	(test == expected) ? (printf(GRN), printf("%s\n", pass)) : (printf(RED), printf("%s\n", fail)) ;
	printf(RESET);
}

void VerifyInt(int test, int expected, char pass[], char fail[])
{
	(test == expected) ? (printf(GRN), printf("%s\n", pass)) : (printf(RED), printf("%s\n", fail)) ;
	printf(RESET);
}

void VerifySizet(size_t test,size_t expected, char pass[], char fail[])
{
	(test == expected) ? (printf(GRN), printf("%s\n", pass)) : (printf(RED), printf("%s\n", fail)) ;
	printf(RESET);
}

void VerifyVoidptr(void* test, void* expected, char pass[], char fail[])
{
	(*(int*)test == *(int*)expected) ? (printf(GRN), printf("%s\n", pass)) : (printf(RED), printf("%s\n", fail)) ;
	printf(RESET);
}

void TestStackCreate()
{
	printf("StackCreate Tests\n");

}
void TestStackDestroy()
{
	printf("StackDestroy Tests\n");
}

void TestStackPush()
{
	printf("StackPush Tests\n");
}

void TestStackPop()
{
	printf("StackPop Tests\n");
}

void TestStackPeek()
{
	printf("StackPeek Tests\n");
}

void TestStackSize()
{
	printf("StackSize Tests\n");
}

void TestStackIsEmpty()
{
	printf("StackIsEmpty Tests\n");
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

    StackPush(stack1,(a+2));
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
}
