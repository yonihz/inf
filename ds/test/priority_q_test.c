/****************************************************************
* 																*
* FILE NAME: priority_q_test.c									*
* 																*
* PURPOSE: Testing priority queue functions						*
* 																*
* DATE: 12.09.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
****************************************************************/

#include <stdio.h>	/* printf */
#include <string.h>	/* strcmp */

#include "priority_q.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"

#define UNUSED(x) (void)(x)

void VerifyInt(int test, int expected, char test_name[]);
void VerifySizet(size_t test,size_t expected, char test_name[]);
void VerifyVoidptr(void* test, void* expected, char test_name[]);
void VerifyChar(char test[], char expected[], char test_name[]);
void VerifyStrncmp(char test[], char expected[], size_t n, char test_name[]);

/* API test functions */

int int_compare(const void* data1, const void* data2, const void* param);
int int_is_smaller(const void* data1, const void* data2, const void* param);
int isNum(const void* data, const void* param);
void TestBasic();

int main()
{
	TestBasic();
	return (0);
}

/* Test functions for API */

void TestBasic()
{
	pq_t* pq1 = NULL;
	int a[10] = {17, 6, 90, 25, 46, 34, 76, 3, 21, 62};
	int a_sorted[10] = {3, 6, 17, 21, 25, 34, 46, 62, 76, 90};
	size_t isNum_match = 34;
	size_t i = 0;
	size_t size = 10;
	void* data_deq = NULL;
	void* data_peek = NULL;
	void* data_erase = NULL;

	printf("Basic Tests\n");

	pq1 = PQCreate(&int_compare, NULL);

	VerifySizet(PQSize(pq1), 0,
	"TEST 1 - SIZE 0 AFTER CREATE");
	VerifyInt(PQIsEmpty(pq1), 1,
	"TEST 2 - ISEMPTY TRUE AFTER CREATE");

	for (i = 0; i < size; i++)
	{
		PQEnqueue(pq1, &a[i]);
	}

	VerifySizet(PQSize(pq1), 10,
	"TEST 3 - SIZE 10 AFTER 10 ENQUEUE");
	VerifyInt(PQIsEmpty(pq1), 0,
	"TEST 4 - ISEMPTY FALSE AFTER 10 ENQUEUE");

	i = 0;
	while (!PQIsEmpty(pq1))
	{
		data_peek = PQPeek(pq1);
		data_deq = PQDequeue(pq1);
		VerifyVoidptr(data_peek, &a_sorted[i],
		"TEST 5 - PEEK");
		VerifyVoidptr(data_deq, &a_sorted[i],
		"TEST 5 - RETURN VALUE OF DEQUEUE");
		i++;
	}

	PQClear(pq1);

	VerifyInt(PQIsEmpty(pq1), 1,
	"TEST 6 - ISEMPTY TRUE AFTER CLEAR");

	for (i = 0; i < size; i++)
	{
		PQEnqueue(pq1, &a[i]);
	}

	data_erase = PQErase(pq1, isNum, &isNum_match);
	VerifyVoidptr(data_erase, &a_sorted[5],
	"TEST 7 - RETURN VALUE OF ERASE");

	PQDestroy(pq1);
}

int int_is_smaller(const void* data1, const void* data2, const void* param)
{
	UNUSED(param);

	if (*(int*)data1 > *(int*)data2)
	{
		return (1);
	}
	return (0);
}

int int_compare(const void* data1, const void* data2, const void* param)
{
	UNUSED(param);

	return (*(int*)data2 - *(int*)data1);
}

int isNum(const void* data, const void* param)
{
	if (*(int*)data == *(int*)param)
	{
		return (0);
	}

	return (1);
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

void VerifyStrncmp(char test[], char expected[], size_t n, char test_name[])
{
	(!strncmp(test, expected, n)) ?
	(printf(GRN), printf("## TEST PASS ## %s\n", test_name)) :
	(printf(RED), printf("## TEST FAIL ## %s\n", test_name)) ;
	printf(RESET);
}
