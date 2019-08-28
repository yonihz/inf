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

int main()
{
	TestStackCreate();
    TestStackDestroy();
    TestStackPush();
    TestStackPop();
    TestStackPeek();
    TestStackSize();
    TestStackIsEmpty();
    
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
