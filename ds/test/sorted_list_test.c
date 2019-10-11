/****************************************************************
* 																*
* FILE NAME: sorted_list_test.c									*
* 																*
* PURPOSE: Testing sorted list functions						*
* 																*
* DATE: 12.09.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
****************************************************************/

#include <stdio.h>	/* printf */
#include <string.h>	/* strcmp */

#include "sorted_list.h"
#include "dlist.h"

#define UNUSED(x) (void)(x)

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"

void VerifyInt(int test, int expected, char test_name[]);
void VerifySizet(size_t test,size_t expected, char test_name[]);
void VerifyVoidptr(void* test, void* expected, char test_name[]);
void VerifyChar(char test[], char expected[], char test_name[]);
void VerifyStrncmp(char test[], char expected[], size_t n, char test_name[]);

/* API test functions */

int int_is_smaller(const void* data1, const void* data2, const void* param);
int is_div_by(const void* data,const void* param);
int set_to_zero(void* data, void* param);
void TestBasic();
void TestFindForEach();
void TestMerge();

int main()
{
	TestBasic();
	TestFindForEach();
	TestMerge();
	return (0);
}

/* Test functions for API */

void TestBasic()
{
	srlist_t* sorted_list1 = NULL;
	sorted_list_iter_t i1;
	int a[10] = {17, 6, 90, 25, 46, 34, 76, 3, 21, 62};
	int a_sorted[10] = {3, 6, 17, 21, 25, 34, 46, 62, 76, 90};
	size_t i = 0;
	size_t size = 10;
	void* data1 = NULL;

	printf("Basic Tests\n");

	sorted_list1 = SortedListCreate(&int_is_smaller, NULL);

	VerifySizet(SortedListSize(sorted_list1), 0,
	"TEST 1 - SIZE 0 AFTER CREATE");
	VerifyInt(SortedListIsEmpty(sorted_list1), 1,
	"TEST 2 - ISEMPTY TRUE AFTER CREATE");

	for (i = 0; i < size; i++)
	{
		SortedListInsert(sorted_list1, &a[i]);
	}

	VerifySizet(SortedListSize(sorted_list1), 10,
	"TEST 3 - SIZE 10 AFTER 10 INSERT");
	VerifyInt(SortedListIsEmpty(sorted_list1), 0,
	"TEST 4 - ISEMPTY FALSE AFTER 10 INSERT");

	i1 = SortedListBegin(sorted_list1);
	i = 0;
	while (!SortedListIsSameIter(i1, SortedListEnd(sorted_list1)))
	{
		data1 = SortedListGetData(i1);
		VerifyVoidptr(data1, &a_sorted[i],
		"TEST 5 - GETDATA AFTER 10 INSERT");
		i1 = SortedListNext(i1);
		i++;
	}

	SortedListPopFront(sorted_list1);
	data1 = SortedListGetData(SortedListBegin(sorted_list1));
	VerifyVoidptr(data1, &a_sorted[1],
		"TEST 6 - GETDATA AFTER POPFRONT");

	SortedListPopBack(sorted_list1);
	data1 = SortedListGetData(SortedListPrev(SortedListEnd(sorted_list1)));
	VerifyVoidptr(data1, &a_sorted[8],
	"TEST 7 - GETDATA AFTER POPBACK");

	SortedListRemove(SortedListBegin(sorted_list1));
	data1 = SortedListGetData(SortedListBegin(sorted_list1));
	VerifyVoidptr(data1, &a_sorted[2],
	"TEST 8 - GETDATA AFTER REMOVE");


	SortedListDestroy(sorted_list1);
}

void TestFindForEach()
{
	srlist_t* sorted_list1 = NULL;
	sorted_list_iter_t i1;
	sorted_list_iter_t start;
	sorted_list_iter_t stop;
	int a[10] = {17, 6, 90, 25, 46, 34, 76, 3, 21, 62};
	int a_sorted[10] = {3, 6, 17, 21, 25, 34, 46, 62, 76, 90};
	int a_sorted_foreach[10] = {3, 6, 0, 0, 0, 34, 46, 62, 76, 90};
	int param1 = 5;
	int param2 = 30;
	size_t i = 0;
	size_t size = 10;
	void* data1 = NULL;

	printf("Find and ForEach Tests\n");

	sorted_list1 = SortedListCreate(&int_is_smaller, NULL);

	for (i = 0; i < size; i++)
	{
		SortedListInsert(sorted_list1, &a[i]);
	}

	start = SortedListBegin(sorted_list1);
	start = SortedListNext(SortedListNext(start));

	stop = SortedListPrev(SortedListEnd(sorted_list1));
	stop = SortedListPrev(SortedListPrev(SortedListPrev(stop)));

	i1 = SortedListFind(sorted_list1, start, stop, &a_sorted[5]);

	data1 = SortedListGetData(i1);
	VerifyVoidptr(data1, &a_sorted[5],
	"TEST 1 - FIND EXISTING DATA IN LIST");

	i1 = SortedListFind(sorted_list1, start, stop, &a_sorted[9]);

	data1 = SortedListGetData(i1);
	VerifyVoidptr(data1, &a_sorted[6],
	"TEST 2 - FIND NON-EXISTING DATA IN LIST");

	i1 = SortedListFindIf(start, stop, is_div_by, &param1);

	data1 = SortedListGetData(i1);
	VerifyVoidptr(data1, &a_sorted[4],
	"TEST 3 - FINDIF WITH MATCH FUNC");

	SortedListForEach(start, stop, set_to_zero, &param2);

	i1 = SortedListBegin(sorted_list1);
	i = 0;
	while (!SortedListIsSameIter(i1, SortedListEnd(sorted_list1)))
	{
		data1 = SortedListGetData(i1);
		VerifyVoidptr(data1, &a_sorted_foreach[i],
		"TEST 4 - GETDATA AFTER FOREACH FUNC");
		i1 = SortedListNext(i1);
		i++;
	}


	SortedListDestroy(sorted_list1);
}

void TestMerge()
{
	srlist_t* sorted_list1 = NULL;
	srlist_t* sorted_list2 = NULL;
	sorted_list_iter_t i1;
	int a_sorted[4] = {3, 6, 17, 39};
	int b_sorted[4] = {1, 5, 20, 34};
	int ab_merged [8] = {1, 3, 5, 6, 17, 20, 34, 39};
	size_t i = 0;
	size_t size = 4;
	void* data1 = NULL;

	printf("Merge Tests\n");

	sorted_list1 = SortedListCreate(&int_is_smaller, NULL);
	sorted_list2 = SortedListCreate(&int_is_smaller, NULL);

	for (i = 0; i < size; i++)
	{
		SortedListInsert(sorted_list1, &a_sorted[i]);
	}

	for (i = 0; i < size; i++)
	{
		SortedListInsert(sorted_list2, &b_sorted[i]);
	}

	SortedListMerge(sorted_list1, sorted_list2);

	i1 = SortedListBegin(sorted_list1);
	i = 0;
	while (!SortedListIsSameIter(i1, SortedListEnd(sorted_list1)))
	{
		data1 = SortedListGetData(i1);
		VerifyVoidptr(data1, &ab_merged[i],
		"TEST 1 - GETDATA OF DEST AFTER MERGE");
		i1 = SortedListNext(i1);
		i++;
	}

	VerifyInt(SortedListIsEmpty(sorted_list2), 1,
	"TEST 2 - ISEMPTY OF SRC IS TRUE AFTER MERGE");

	SortedListDestroy(sorted_list1);
}

int int_is_smaller(const void* data1, const void* data2, const void* param)
{
	UNUSED(param);

	if (*(int*)data1 < *(int*)data2)
	{
		return (1);
	}
	return (0);
}

int is_div_by(const void* data,const void* param)
{
	if ((*(int*)data % *(int*)param) == 0)
	{
		return (0);
	}
	return (1);
}

/* set to zero if data not bigger than param */
int set_to_zero(void* data, void* param)
{
	if ((*(int*)data > *(int*)param))
	{
		return (1);
	}

	*(int*)data = 0;
	return (0);
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
