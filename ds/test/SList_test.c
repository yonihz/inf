/****************************************************************
* 																*
* FILE NAME: vector_test.c										*
* 																*
* PURPOSE: Testing vector functions								*
*                                                               *
* VERSION: 0.1													*
* 																*
* DATE: 29.08.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
* Reviewer: Tal Samucha												*
* 																*
****************************************************************/

#include <stdio.h>	/* printf */
#include <string.h>	/* strcmp */
#include <stdlib.h>	/* free */

#include "SList.h"

/* colors for test results */

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"

/* debug test functions */

#ifndef NDEBUG

#endif

/* API test functions */

void TestSListCreate();
void TestSListInsertAfter();
void TestSListInsert();
void TestSListRemoveAfter();
void TestSListRemove();

int main()
{
	TestSListCreate();
	TestSListInsertAfter();
	TestSListInsert();
	TestSListRemoveAfter();
	TestSListRemove();

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

void TestSListCreate()
{
	char char1 = 'A';
	char char2 = 'B';
	char char3 = 'C';

	slist_node_t* head1 = NULL;
	slist_node_t* node1 = NULL;

	printf("Create Tests\n");

	head1 = SListCreateNode(&char1, NULL);
	
	VerifyChar(head1->data, &char1,
	"TEST 1 - CREATE LIST WITH 1 NODE");
	
	SListFreeAll(head1);

	head1 = SListCreateNode(&char1,
	SListCreateNode(&char2, SListCreateNode(&char3, NULL)));

	node1 = head1;
	VerifyChar(node1->data, &char1,
	"TEST 2 - CREATE CHAIN - CHECK NODE 1");

	node1 = node1->next;
	VerifyChar(node1->data, &char2,
	"TEST 3 - CREATE CHAIN - CHECK NODE 2");

	node1 = node1->next;
	VerifyChar(node1->data, &char3,
	"TEST 4 - CREATE CHAIN - CHECK NODE 3");

	SListFreeAll(head1);	
}

void TestSListInsertAfter()
{
	char str_test[] = "ABCDE";
	char insert = 'X';
	size_t len = 0;
	size_t n = 0;
	size_t i = 0;
	slist_node_t* head_list1 = NULL;
	slist_node_t* node_list1 = NULL;
	slist_node_t* node_n_list1 = NULL;
	
	len = strlen(str_test);


	printf("InsertAfter Tests\n");
	
	head_list1 = NULL;
	node_list1 = NULL;
	node_n_list1 = NULL;	
	i = 0;
	while (*(str_test + i))
	{
		head_list1 = SListCreateNode((str_test + len - 1 - i), head_list1);
		i++;
	}

	for (n = 0, node_n_list1 = head_list1, i = 0; i < n; i++)
	{
		node_n_list1 = node_n_list1->next;
	}

	node_list1 = SListInsertAfter(node_n_list1, SListCreateNode(&insert, NULL));

	VerifyChar(node_list1->data, &insert,
	"TEST 1 - CHECK RETURN VALUE IS NEW NODE");

	VerifyChar((node_n_list1->next)->data, &insert,
	"TEST 2 - CHECK NODE IS INSERTED AFTER FIRST NODE");
	
	SListFreeAll(head_list1);

	head_list1 = NULL;
	node_list1 = NULL;
	node_n_list1 = NULL;	
	i = 0;
	while (*(str_test + i))
	{
		head_list1 = SListCreateNode((str_test + len - 1 - i), head_list1);
		i++;
	}

	for (n = 2, node_n_list1 = head_list1, i = 0; i < n; i++)
	{
		node_n_list1 = node_n_list1->next;
	}

	node_list1 = SListInsertAfter(node_n_list1, SListCreateNode(&insert, NULL));

	VerifyChar((node_n_list1->next)->data, &insert,
	"TEST 3 - CHECK NODE IS INSERTED AFTER 3RD NODE");
	
	SListFreeAll(head_list1);

	head_list1 = NULL;
	node_list1 = NULL;
	node_n_list1 = NULL;
	i = 0;
	while (*(str_test + i))
	{
		head_list1 = SListCreateNode((str_test + len - 1 - i), head_list1);
		i++;
	}

	for (n = 4, node_n_list1 = head_list1, i = 0; i < n; i++)
	{
		node_n_list1 = node_n_list1->next;
	}

	node_list1 = SListInsertAfter(node_n_list1, SListCreateNode(&insert, NULL));

	VerifyChar((node_n_list1->next)->data, &insert,
	"TEST 4 - CHECK NODE IS INSERTED AFTER LAST NODE");
	
	SListFreeAll(head_list1);
}

void TestSListInsert()
{
	char str_test[] = "ABCDE";
	char insert = 'X';
	size_t len = 0;
	size_t n = 0;
	size_t i = 0;
	slist_node_t* head_list1 = NULL;
	slist_node_t* node_list1 = NULL;
	slist_node_t* node_n_list1 = NULL;
	
	len = strlen(str_test);


	printf("Insert Tests\n");
	
	head_list1 = NULL;
	node_list1 = NULL;
	node_n_list1 = NULL;
	i = 0;
	while (*(str_test + i))
	{
		head_list1 = SListCreateNode((str_test + len - 1 - i), head_list1);
		i++;
	}

	for (n = 0, node_n_list1 = head_list1, i = 0; i < n; i++)
	{
		node_n_list1 = node_n_list1->next;
	}

	node_list1 = SListInsert(node_n_list1, SListCreateNode(&insert, NULL));

	VerifyChar(node_list1->data, (str_test + n),
	"TEST 1 - CHECK RETURN VALUE IS TARGET");

	VerifyChar((node_n_list1->next)->data, (str_test + n),
	"TEST 2 - CHECK NODE IS INSERTED BEFORE FIRST NODE");
	
	SListFreeAll(head_list1);

	head_list1 = NULL;
	node_list1 = NULL;
	node_n_list1 = NULL;	
	i = 0;
	while (*(str_test + i))
	{
		head_list1 = SListCreateNode((str_test + len - 1 - i), head_list1);
		i++;
	}

	for (n = 2, node_n_list1 = head_list1, i = 0; i < n; i++)
	{
		node_n_list1 = node_n_list1->next;
	}

	node_list1 = SListInsert(node_n_list1, SListCreateNode(&insert, NULL));

	VerifyChar((node_n_list1->next)->data, (str_test + n),
	"TEST 3 - CHECK NODE IS INSERTED BEFORE 3RD NODE");
	
	SListFreeAll(head_list1);

	head_list1 = NULL;
	node_list1 = NULL;
	node_n_list1 = NULL;	
	i = 0;
	while (*(str_test + i))
	{
		head_list1 = SListCreateNode((str_test + len - 1 - i), head_list1);
		i++;
	}

	for (n = 4, node_n_list1 = head_list1, i = 0; i < n; i++)
	{
		node_n_list1 = node_n_list1->next;
	}

	node_list1 = SListInsert(node_n_list1, SListCreateNode(&insert, NULL));

	VerifyChar((node_n_list1->next)->data, (str_test + n),
	"TEST 4 - CHECK NODE IS INSERTED BEFORE LAST NODE");
	
	SListFreeAll(head_list1);
}

void TestSListRemoveAfter()
{
	char str_test[] = "ABCDE";
	size_t len = 0;
	size_t n = 0;
	size_t i = 0;
	slist_node_t* head_list1 = NULL;
	slist_node_t* node_list1 = NULL;
	slist_node_t* node_n_list1 = NULL;
	
	len = strlen(str_test);


	printf("RemoveAfter Tests\n");
	
	head_list1 = NULL;
	node_list1 = NULL;
	node_n_list1 = NULL;	
	i = 0;
	while (*(str_test + i))
	{
		head_list1 = SListCreateNode((str_test + len - 1 - i), head_list1);
		i++;
	}

	for (n = 0, node_n_list1 = head_list1, i = 0; i < n; i++)
	{
		node_n_list1 = node_n_list1->next;
	}

	node_list1 = SListRemoveAfter(node_n_list1);

	VerifyChar(node_list1->data, (str_test + n + 2),
	"TEST 1 - CHECK RETURN VALUE IS AFTER ERASED NODE");

	VerifyChar((node_n_list1->next)->data, (str_test + n + 2),
	"TEST 2 - CHECK NODE REMOVED IS AFTER FIRST");
	
	SListFreeAll(head_list1);

	head_list1 = NULL;
	node_list1 = NULL;
	node_n_list1 = NULL;	
	i = 0;
	while (*(str_test + i))
	{
		head_list1 = SListCreateNode((str_test + len - 1 - i), head_list1);
		i++;
	}

	for (n = 2, node_n_list1 = head_list1, i = 0; i < n; i++)
	{
		node_n_list1 = node_n_list1->next;
	}

	node_list1 = SListRemoveAfter(node_n_list1);

	VerifyChar((node_n_list1->next)->data, (str_test + n + 2),
	"TEST 3 - CHECK NODE REMOVED IS AFTER 3RD");
	
	SListFreeAll(head_list1);

	head_list1 = NULL;
	node_list1 = NULL;
	node_n_list1 = NULL;	
	i = 0;
	while (*(str_test + i))
	{
		head_list1 = SListCreateNode((str_test + len - 1 - i), head_list1);
		i++;
	}

	for (n = 4, node_n_list1 = head_list1, i = 0; i < n; i++)
	{
		node_n_list1 = node_n_list1->next;
	}

	node_list1 = SListRemoveAfter(node_n_list1);

	VerifySListt(node_list1, NULL,
	"TEST 4 - CHECK RETURN VALUE IS NULL ON LAST NODE");
	
	SListFreeAll(head_list1);
}

void TestSListRemove()
{
	char str_test[] = "ABCDE";
	size_t len = 0;
	size_t n = 0;
	size_t i = 0;
	slist_node_t* head_list1 = NULL;
	slist_node_t* node_list1 = NULL;
	slist_node_t* node_n_list1 = NULL;
	
	len = strlen(str_test);


	printf("Remove Tests\n");
	
	head_list1 = NULL;
	node_list1 = NULL;
	node_n_list1 = NULL;	
	i = 0;
	while (*(str_test + i))
	{
		head_list1 = SListCreateNode((str_test + len - 1 - i), head_list1);
		i++;
	}

	for (n = 0, node_n_list1 = head_list1, i = 0; i < n; i++)
	{
		node_n_list1 = node_n_list1->next;
	}

	node_list1 = SListRemove(node_n_list1);

	VerifyChar(node_list1->data, (str_test + n + 1),
	"TEST 1 - CHECK RETURN VALUE IS AFTER ERASED NODE");

	head_list1 = node_list1;
	for (n = 0, node_n_list1 = head_list1, i = 0; i < n; i++)
	{
		node_n_list1 = node_n_list1->next;
	}

	VerifyChar(node_n_list1->data, (str_test + n + 1),
	"TEST 2 - CHECK NODE REMOVED IS AFTER FIRST");
	
	SListFreeAll(head_list1);

	head_list1 = NULL;
	node_list1 = NULL;
	node_n_list1 = NULL;	
	i = 0;
	while (*(str_test + i))
	{
		head_list1 = SListCreateNode((str_test + len - 1 - i), head_list1);
		i++;
	}

	for (n = 2, node_n_list1 = head_list1, i = 0; i < n; i++)
	{
		node_n_list1 = node_n_list1->next;
	}

	node_list1 = SListRemove(node_n_list1);

	for (n = 2, node_n_list1 = head_list1, i = 0; i < n; i++)
	{
		node_n_list1 = node_n_list1->next;
	}

	VerifyChar((node_n_list1->next)->data, (str_test + n + 2),
	"TEST 3 - CHECK NODE REMOVED IS AFTER 3RD");
	
	SListFreeAll(head_list1);
}



/* Test functions for debug version */

#ifndef NDEBUG

#endif
