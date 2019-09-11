/****************************************************************
* 																*
* FILE NAME: dlist_test.c										*
* 																*
* PURPOSE: Testing dlist functions								*
*                                                               *
* VERSION: 0.1													*
* 																*
* DATE: 10.09.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
* Reviewer: N/A													*
* 																*
****************************************************************/

#include <stdio.h>	/* printf */
#include <string.h> /* strlen */
#include <time.h> /* time */
#include <stdlib.h> /* srand */

#include "dlist.h"
#include "verify_funcs.h"

/* API test functions */

void TestBasic();
void TestTraverseFuncs();

int main()
{
	srand(time(NULL));
	TestBasic();
	TestTraverseFuncs();
    
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
	i1 = DListInsert(dlist1, DListBegin(dlist1), (&a + 0));
	i2 = DListInsert(dlist1, DListBegin(dlist1), (&a + 1));
	VerifyVoidptr(DListGetData(i1), (&a + 0),
	"TEST1 - CREATE, INSERT TO BEGIN AND GET DATA");
	VerifyVoidptr(DListGetData(i2), (&a + 1),
	"TEST2 - INSERT TO BEGIN AND GET DATA");
	i3 = DListInsert(dlist1, DListEnd(dlist1), (&a + 2));
	DListInsert(dlist1, DListEnd(dlist1), (&a + 3));
	VerifyVoidptr(DListGetData(DListEnd(dlist1)), (&a + 3),
	"TEST3 - GET DATA OF LAST ELEMENT (END)");
	VerifyVoidptr(DListGetData(DListNext(DListEnd(dlist1))), (&a + 2),
	"TEST4 - GET DATA OF NEXT TO LAST ELEMENT (END NEXT)");
	VerifyVoidptr(DListGetData(DListPrev(DListBegin(dlist1))), (&a + 1),
	"TEST5 - GET DATA OF FIRST ELEMENT (BEGIN PREV)");
	VerifyVoidptr(DListGetData(DListRemove(i3)), (&a + 0),
	"TEST6 - REMOVE AND GET DATA OF RETURNED ITER");
	DListPushFront(dlist1, (&a + 4));
	DListPushBack(dlist1, (&a + 5));
	VerifyVoidptr(DListGetData(DListEnd(dlist1)), (&a + 5),
	"TEST7 - PUSHBACK GET DATA OF LAST ELEMENT (END)");
	VerifyVoidptr(DListGetData(DListPrev(DListBegin(dlist1))), (&a + 4),
	"TEST8 - PUSHFRONT AND GET DATA OF FIRST ELEMENT (BEGIN PREV)");
	DListPopFront(dlist1);
	DListPopBack(dlist1);
	VerifyVoidptr(DListGetData(DListEnd(dlist1)), (&a + 3),
	"TEST9 - POPBACK GET DATA OF LAST ELEMENT (END)");
	VerifyVoidptr(DListGetData(DListPrev(DListBegin(dlist1))), (&a + 1),
	"TEST10 - POPFRONT AND GET DATA OF FIRST ELEMENT (BEGIN PREV)");

	DListDestroy(dlist1);
}

void TestTraverseFuncs()
{
	dlist_t* dlist1 = NULL;
	/*dlist_iter_t i1 = NULL, i2 = NULL, i3 = NULL, i4 = NULL;*/
	int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	printf("Traverse Functions Tests\n");

	dlist1 = DListCreate();

	VerifySizet(DListSize(dlist1), 0,
	"TEST1 - SIZE OF EMPTY LIST AFTER CREATE (FOREACH)");
	VerifyInt(DListIsEmpty(dlist1), 1,
	"TEST2 - ISEMPTY OF EMPTY LIST AFTER CREATE");
	DListInsert(dlist1, DListBegin(dlist1), (&a + 0));
	DListInsert(dlist1, DListBegin(dlist1), (&a + 1));
	DListInsert(dlist1, DListBegin(dlist1), (&a + 2));
	DListInsert(dlist1, DListBegin(dlist1), (&a + 3));
	VerifySizet(DListSize(dlist1), 4,
	"TEST3 - SIZE OF LIST AFTER INSERT (FOREACH)");
	VerifyInt(DListIsEmpty(dlist1), 0,
	"TEST4 - ISEMPTY OF LIST AFTER INSERT");
	DListPopFront(dlist1);
	DListPopFront(dlist1);
	DListPopFront(dlist1);
	DListPopFront(dlist1);
	VerifySizet(DListSize(dlist1), 0,
	"TEST5 - SIZE OF EMPTY LIST AFTER REMOVE (FOREACH)");
	VerifyInt(DListIsEmpty(dlist1), 1,
	"TEST6 - ISEMPTY OF EMPTY LIST AFTER REMOVE");

	DListDestroy(dlist1);
}
