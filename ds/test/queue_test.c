/****************************************************************
* 																*
* FILE NAME: queue_test.c										*
* 																*
* PURPOSE: Testing queue functions								*
*                                                               *
* VERSION: 0.1													*
* 																*
* DATE: 04.09.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
* Reviewer: N/A												*
* 																*
****************************************************************/

#include <stdio.h>	/* printf */
#include <string.h>	/* strcmp */
#include <stdlib.h>	/* free */

#include "queue.h"
#include "slist.h"

/* colors for test results */

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"

/* debug test functions */

#ifndef NDEBUG

#endif

/* API test functions */

void TestQCreateAndEnq();
void TestQEnqDeqAndPeek();

struct queue
{
	slist_node_t* first;
	slist_node_t* last;
};

int main()
{
	TestQCreateAndEnq();
	TestQEnqDeqAndPeek();

#ifndef NDEBUG

#endif
    
	return (0);
}

/* verify functions - compare to expected value and print pass/fail */

void VerifySListt(slist_node_t* test, slist_node_t* expected, char test_name[])
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

void TestQCreateAndEnq()
{
	int a = 14, b = 32;
	queue_t* queue1 = NULL;
	slist_node_t* dummy = NULL;
	slist_node_t* last = NULL;

	printf("Create and Enqueue Tests\n");
	
	queue1 = QCreate();

	dummy = queue1->first;

	VerifySListt(dummy->next, NULL,
	"TEST1  - CREATE AND CHECK DUMMY NEXT");

	VerifyVoidptr(dummy->data, NULL,
	"TEST2  - CREATE AND CHECK DUMMY DATA");

	QEnqueue(queue1, &a);
	last = queue1->last;

	VerifyVoidptr((dummy->next)->data, &a,
	"TEST3  - 1 ENQUEUE AND CHECK QUEUE STRUCT FIRST");

	VerifyVoidptr(last->data, &a,
	"TEST4  - 1 ENQUEUE AND CHECK QUEUE STRUCT LAST");

	QEnqueue(queue1, &b);
	last = queue1->last;

	VerifyVoidptr((dummy->next)->data, &a,
	"TEST5  - 2 ENQUEUE AND CHECK QUEUE STRUCT FIRST");

	VerifyVoidptr(last->data, &b,
	"TEST6  - 2 ENQUEUE AND CHECK QUEUE STRUCT LAST");

	QDequeue(queue1);
	last = queue1->last;

	VerifyVoidptr((dummy->next)->data, &b,
	"TEST7  - 1 DEQUEUE AND CHECK QUEUE STRUCT FIRST");

	VerifyVoidptr(last->data, &b,
	"TEST8  - 1 DEQUEUE AND CHECK QUEUE STRUCT LAST");

	QDequeue(queue1);
	last = queue1->last;

	VerifyVoidptr((dummy->next)->data, NULL,
	"TEST9  - 2 DEQUEUE AND CHECK QUEUE STRUCT FIRST");

	QEnqueue(queue1, &a);
	last = queue1->last;

	VerifyVoidptr((dummy->next)->data, &a,
	"TEST10 - 1 ENQUEUE AND CHECK QUEUE STRUCT FIRST");

	VerifyVoidptr(last->data, &a,
	"TEST11 - 1 ENQUEUE AND CHECK QUEUE STRUCT LAST");

	QDestroy(queue1);
}

void TestQEnqDeqAndPeek()
{
	int a = 14, b = 32;
	queue_t* queue1 = NULL;

	printf("Enqueue Dequeue and Peek Tests\n");
	
	queue1 = QCreate();

	QEnqueue(queue1, &a);

	VerifyVoidptr(QPeek(queue1), &a,
	"TEST1 - 2 ENQUEUE AND CHECK QUEUE STRUCT FIRST");

	QEnqueue(queue1, &b);

	VerifyVoidptr(QPeek(queue1), &a,
	"TEST2 - 2 ENQUEUE AND CHECK QUEUE STRUCT FIRST");

	QDequeue(queue1);

	VerifyVoidptr(QPeek(queue1), &b,
	"TEST3 - 2 ENQUEUE AND CHECK QUEUE STRUCT FIRST");

	QDestroy(queue1);
}

/* Test functions for debug version */

#ifndef NDEBUG

#endif
