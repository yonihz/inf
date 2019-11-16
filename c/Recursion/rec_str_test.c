/****************************************************************
* 																*
* FILE NAME: rec_str_test.c							    	   	*
* 																*
* PURPOSE: Testing recursion functions	        			    *
*                                                               *
* DATE: 01.11.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
****************************************************************/

#include <stdio.h>

#include "rec_str.h"
#include "slist.h"
#include "stack.h"

#define STACK_SIZE 5

void TestFib(unsigned int n);
void TestSortStack(void);

int main()
{
    /*
    TestFib(0);
    TestFib(1);
    TestFib(2);
    TestFib(3);
    TestFib(4);
    TestFib(5);
    TestFib(6);
    */

    TestSortStack();

    return (0);
}

void TestSortStack(void)
{
	stack_t* stack1 = NULL;
    size_t num_of_elements = STACK_SIZE;
    size_t size_of_elements = sizeof(int);
    int a[5] = {2, 3, 1, 5, 4};
    size_t i = 0;

	printf("SortUnsortedStack Tests\n");
    stack1 = StackCreate(num_of_elements, size_of_elements);

    for (i = 0; i < STACK_SIZE; i++)
    {
        StackPush(stack1, (a+i));
    }

	printf("Before sort:\n");
    for (i = 0; i < STACK_SIZE; i++)
    {
        printf("Element %lu: %d\n", i, *(int*)StackPeek(stack1));
        StackPop(stack1);
    }
    
    for (i = 0; i < STACK_SIZE; i++)
    {
        StackPush(stack1, (a+i));
    }

    SortUnsortedStack(stack1);

	printf("After sort:\n");
    for (i = 0; i < STACK_SIZE; i++)
    {
        printf("Element %lu: %d\n", i, *(int*)StackPeek(stack1));
        StackPop(stack1);
    }

    StackDestroy(stack1);
}

void TestFib(unsigned int n)
{
    printf("Test Fibonacci with n=%u\n", n);
    printf("Iterative: %u\n", ItrFib(n));
    printf("Recursive: %u\n\n", RecFib(n));   
}