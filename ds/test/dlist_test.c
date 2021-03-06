/****************************************************************
* 																*
* FILE NAME: dlist_test.c										*
* 																*
* PURPOSE: Testing dlist functions								*
* 																*
* DATE: 10.09.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
****************************************************************/

#include <stdio.h>	/* printf */
#include <string.h>	/* strcmp */

#include "dlist.h"

/* colors for test results */

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"

void VerifyInt(int test, int expected, char test_name[]);
void VerifySizet(size_t test,size_t expected, char test_name[]);
void VerifyVoidptr(void* test, void* expected, char test_name[]);
void VerifyChar(char test[], char expected[], char test_name[]);
void VerifyStrncmp(char test[], char expected[], size_t n, char test_name[]);

/* API test functions */

void TestBasic();
void TestTraverseFuncs();
void TestSplice();
int isNum(const void* data, const void* param);

int main()
{
	TestBasic();
	TestTraverseFuncs();
	TestSplice();
    
	return (0);
}

/* Test functions for API */

void TestBasic()
{
	dlist_t* dlist1 = NULL;
	dlist_iter_t i1 = NULL, i2 = NULL, i3 = NULL;
	int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	printf("Basic Tests\n");

	dlist1 = DListCreate();
	i1 = DListInsert(dlist1, DListBegin(dlist1), &a[0]);
	i2 = DListInsert(dlist1, DListBegin(dlist1), &a[1]);
	VerifyVoidptr(DListGetData(i1), &a[0],
	"TEST1 - CREATE, INSERT TO BEGIN AND GET DATA");
	VerifyVoidptr(DListGetData(i2), &a[1],
	"TEST2 - INSERT TO BEGIN AND GET DATA");
	i3 = DListInsert(dlist1, DListEnd(dlist1), &a[2]);
	DListInsert(dlist1, DListEnd(dlist1), &a[3]);
	VerifyVoidptr(DListGetData(DListPrev(DListEnd(dlist1))), &a[3],
	"TEST3 - GET DATA OF LAST ELEMENT (END-PREV)");
	VerifyVoidptr(DListGetData(DListPrev(DListPrev(DListEnd(dlist1)))), &a[2],
	"TEST4 - GET DATA OF NEXT TO LAST ELEMENT (END-PREV-PREV)");
	VerifyVoidptr(DListGetData(DListBegin(dlist1)), &a[1],
	"TEST5 - GET DATA OF FIRST ELEMENT (BEGIN)");
	VerifyVoidptr(DListGetData(DListRemove(i3)), &a[3],
	"TEST6 - REMOVE AND GET DATA OF RETURNED ITER");
	DListPushFront(dlist1, &a[4]);
	DListPushBack(dlist1, &a[5]);
	VerifyVoidptr(DListGetData(DListPrev(DListEnd(dlist1))), &a[5],
	"TEST7 - PUSHBACK GET DATA OF LAST ELEMENT (END PREV)");
	VerifyVoidptr(DListGetData(DListBegin(dlist1)), &a[4],
	"TEST8 - PUSHFRONT AND GET DATA OF FIRST ELEMENT (BEGIN)");
	DListPopFront(dlist1);
	DListPopBack(dlist1);
	VerifyVoidptr(DListGetData((DListPrev(DListEnd(dlist1)))), &a[3],
	"TEST9 - POPBACK GET DATA OF LAST ELEMENT (END PREV)");
	VerifyVoidptr(DListGetData(DListBegin(dlist1)), &a[1],
	"TEST10 - POPFRONT AND GET DATA OF FIRST ELEMENT (BEGIN PREV)");

	DListDestroy(dlist1);
}

void TestTraverseFuncs()
{
	dlist_t* dlist1 = NULL;
	dlist_iter_t i1 = NULL;
	int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	printf("Traverse Functions Tests\n");

	dlist1 = DListCreate();
	VerifySizet(DListSize(dlist1), 0,
	"TEST1 - SIZE OF EMPTY LIST AFTER CREATE (FOREACH)");
	VerifyInt(DListIsEmpty(dlist1), 1,
	"TEST2 - ISEMPTY OF EMPTY LIST AFTER CREATE");
	DListInsert(dlist1, DListBegin(dlist1), &a[0]);
	DListInsert(dlist1, DListBegin(dlist1), &a[1]);
	DListInsert(dlist1, DListBegin(dlist1), &a[2]);
	DListInsert(dlist1, DListBegin(dlist1), &a[3]);
	VerifySizet(DListSize(dlist1), 4,
	"TEST3 - SIZE OF LIST AFTER INSERT (FOREACH)");
	VerifyInt(DListIsEmpty(dlist1), 0,
	"TEST4 - ISEMPTY OF LIST AFTER INSERT");
	i1 = DListFind(DListBegin(dlist1), DListEnd(dlist1), &isNum, &a[2]); 
	VerifyVoidptr(DListGetData(i1), &a[2],
	"TEST5 - FIND EXISTING DATA IN LIST");
	i1 = DListFind(DListBegin(dlist1), DListEnd(dlist1), &isNum, &a[9]);
	VerifyInt(DListIsSame(i1, DListEnd(dlist1)), 1,
	"TEST6 - FIND NON-EXISTING DATA AND LIST AND USE ISSAME");
	DListPopFront(dlist1);
	DListPopFront(dlist1);
	DListPopFront(dlist1);
	DListPopFront(dlist1);
	VerifySizet(DListSize(dlist1), 0,
	"TEST7 - SIZE OF EMPTY LIST AFTER REMOVE (FOREACH)");
	VerifyInt(DListIsEmpty(dlist1), 1,
	"TEST8 - ISEMPTY OF EMPTY LIST AFTER REMOVE");

	DListDestroy(dlist1);
}

void TestSplice()
{
	dlist_t* dlist1 = NULL;
	dlist_t* dlist2 = NULL;
	dlist_iter_t iter_src_start = NULL;
	dlist_iter_t iter_src_stop = NULL;
	dlist_iter_t iter_dest = NULL;
	dlist_iter_t iter_list1 = NULL;
	dlist_iter_t iter_list2 = NULL;
	int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int b[10] = {20, 21, 22, 23, 24, 25, 26, 27, 28, 29};
	int a_splice[14] = {0, 1, 2, 22, 23, 24, 25, 3, 4, 5, 6, 7, 8, 9};
	int b_splice[6] = {20, 21, 26, 27, 28, 29};
	int i = 0;
	int size = 10;

	printf("Splice Tests\n");

	dlist1 = DListCreate();
	dlist2 = DListCreate();
	for (i = 0; i < size; i++)
	{
		DListPushBack(dlist1, &a[i]);
		DListPushBack(dlist2, &b[i]);	
	}

	iter_src_start = DListBegin(dlist2);
	iter_dest = DListBegin(dlist1);

	for (i = 0; i < 2; i++)
	{
		iter_src_start = DListNext(iter_src_start);
	}

	iter_src_stop = iter_src_start;

	for (i = 0; i < 4; i++)
	{
		iter_src_stop = DListNext(iter_src_stop);
	}

	for (i = 0; i < 3; i++)
	{
		iter_dest = DListNext(iter_dest);
	}

	DListSplice(iter_dest, iter_src_start, iter_src_stop);
	iter_list1 = DListBegin(dlist1);
	iter_list2 = DListBegin(dlist2);

	for (i = 0; i < 14; i++)
	{
		VerifyVoidptr(DListGetData(iter_list1), &a_splice[i],
		"TEST - GETDATA OF SPLICE DEST LIST");
		iter_list1 = DListNext(iter_list1);
	}

	for (i = 0; i < 6; i++)
	{
		VerifyVoidptr(DListGetData(iter_list2), &b_splice[i],
		"TEST - GETDATA OF SPLICE SRC LIST");
		iter_list2 = DListNext(iter_list2);
	}

	DListDestroy(dlist1);
	DListDestroy(dlist2);
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
