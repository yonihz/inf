/****************************************************************
* 																*
* FILE NAME: queue_test.c										*
* 																*
* PURPOSE: Testing queue functions								*
*                                                               *
* DATE: 04.09.19												*
* 																*
* Author: Yoni Horovitz											*
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

void TestQFirstLast();
void TestQEnqDeqAndPeek();
void TestQSize();
void TestQAppend();

struct queue
{
	slist_node_t* first;
	slist_node_t* last;
};

int main()
{
	TestQFirstLast();
	TestQEnqDeqAndPeek();
	TestQSize();
	TestQAppend();

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

void TestQFirstLast()
{
	int a = 14, b = 32;
	queue_t* queue1 = NULL;
	slist_node_t* dummy = NULL;
	slist_node_t* last = NULL;

	printf("Queue First Last Tests\n");
	
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

	VerifySListt(dummy->next, NULL,
	"TEST9 -  2 DEQUEUE AND CHECK QUEUE STRUCT FIRST");

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
	"TEST1 - 1 ENQUEUE AND PEEK");

	QEnqueue(queue1, &b);

	VerifyVoidptr(QPeek(queue1), &a,
	"TEST2 - 2 ENQUEUE AND PEEK");

	QDequeue(queue1);

	VerifyVoidptr(QPeek(queue1), &b,
	"TEST3 - 1 DEQUEUE AND PEEK");

	QDequeue(queue1);

	VerifyVoidptr(QPeek(queue1), NULL,
	"TEST4 - 2 DEQUEUE (EMPTY) AND PEEK");

	QEnqueue(queue1, &a);

	VerifyVoidptr(QPeek(queue1), &a,
	"TEST5 - 1 ENQUEUE AND PEEK");

	QDestroy(queue1);
}

void TestQSize()
{
	int a = 14, b = 32;
	queue_t* queue1 = NULL;

	printf("Size Tests\n");
	
	queue1 = QCreate();

	VerifySizet(QSize(queue1), 0,
	"TEST1 - SIZE EMPTY QUEUE");

	VerifyInt(QIsEmpty(queue1), 1,
	"TEST2 - ISEMPTY EMPTY QUEUE");

	QEnqueue(queue1, &a);

	VerifySizet(QSize(queue1), 1,
	"TEST3 - SIZE 1 ENQUEUE");

	VerifyInt(QIsEmpty(queue1), 0,
	"TEST4 - ISEMPTY NON-EMPTY QUEUE");

	QEnqueue(queue1, &b);

	VerifySizet(QSize(queue1), 2,
	"TEST5 - SIZE 2 ENQUEUE");

	QDequeue(queue1);

	VerifySizet(QSize(queue1), 1,
	"TEST6 - SIZE 1 DEQUEUE");

	QDequeue(queue1);

	VerifySizet(QSize(queue1), 0,
	"TEST7 - SIZE 2 DEQUEUE (EMPTY)");

	VerifyInt(QIsEmpty(queue1), 1,
	"TEST8 - ISEMPTY EMPTY QUEUE");

	QEnqueue(queue1, &a);

	VerifySizet(QSize(queue1), 1,
	"TEST9 - SIZE 1 ENQUEUE");

	QDestroy(queue1);
}

void TestQAppend()
{
	int q11 = 14, q12 = 32, q13 = 47, q14 = 9, q15 = 98;
	int q21 = 23, q22 = 67, q23 = 89, q24 = 13, q25 = 78;

	slist_node_t* last1 = NULL;
	slist_node_t* last2 = NULL;
	queue_t* queue1 = NULL;
	queue_t* queue2 = NULL;

	printf("Append Tests\n");
	
	queue1 = QCreate();
	queue2 = QCreate();

	QEnqueue(queue1, &q11);
	QEnqueue(queue1, &q12);
	QEnqueue(queue1, &q13);
	QEnqueue(queue1, &q14);

	QEnqueue(queue2, &q21);
	QEnqueue(queue2, &q22);
	QEnqueue(queue2, &q23);

	VerifySizet(QSize(queue1), 4,
	"TEST1 - SIZE QUEUE1 - 4 ENQUEUE");

	VerifySizet(QSize(queue2), 3,
	"TEST2 - SIZE QUEUE2 - 3 ENQUEUE");

	QAppend(queue1, queue2);

	VerifySizet(QSize(queue1), 7,
	"TEST3 - SIZE QUEUE 1 IS 7 AFTER APPEND");

	VerifyInt(QIsEmpty(queue2), 1,
	"TEST4 - SIZE QUEUE 2 IS 0 AFTER APPEND");

	VerifyVoidptr(QPeek(queue1), &q11,
	"TEST5 - PEEK QUEUE 1 AFTER APPEND");

	VerifyVoidptr(QPeek(queue2), NULL,
	"TEST6 - PEEK QUEUE 2 AFTER APPEND");

	last1 = queue1->last;

	VerifyVoidptr(last1->data, &q23,
	"TEST7  - CHECK QUEUE1 STRUCT LAST AFTER APPEND");

	QEnqueue(queue1, &q15);
	QEnqueue(queue2, &q24);
	QEnqueue(queue2, &q25);

	last1 = queue1->last;
	last2 = queue2->last;

	VerifyVoidptr(last1->data, &q15,
	"TEST8  - CHECK QUEUE1 STRUCT LAST AFTER 1 ENQ");

	VerifyVoidptr(last2->data, &q25,
	"TEST9  - CHECK QUEUE2 STRUCT LAST AFTER 2 ENQ");

	QDestroy(queue1);
	QDestroy(queue2);
}

/* Test functions for debug version */

#ifndef NDEBUG

#endif
