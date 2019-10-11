/****************************************************************
* 																*
* FILE NAME: uid_test.c											*
* 																*
* PURPOSE: Testing UID functions								*
* 																*
* DATE: 12.09.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
****************************************************************/

#include <stdio.h>	/* printf */
#include <string.h>	/* strcmp */

#include "uid.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"

void VerifyInt(int test, int expected, char test_name[]);
void VerifySizet(size_t test,size_t expected, char test_name[]);
void VerifyVoidptr(void* test, void* expected, char test_name[]);
void VerifyChar(char test[], char expected[], char test_name[]);
void VerifyStrncmp(char test[], char expected[], size_t n, char test_name[]);

/* API test functions */

void TestCreate();

int main()
{
	TestCreate();
	return (0);
}

/* Test functions for API */

void TestCreate()
{
	size_t i = 0;
	size_t size = 3;
	ilrd_uid_t uid_arr[3];

	printf("TEST 1 - CREATE 3 UID'S WITH 1SEC DELAY\n");
	for (i = 0; i < size; i++)
	{
		uid_arr[i] = UIDCreate();
		sleep(1);
	}

	printf("counter		time		pid\n");
	for (i = 0; i < size; i++)
	{
		printf("%lu		%lu	%d\n",
		uid_arr[i].counter, uid_arr[i].time, uid_arr[i].pid);
	}

	VerifyInt(UIDIsSame(uid_arr[0],uid_arr[0]), 1,
	"TEST2 - ISSAME TRUE FOR SAME UID'S");

	VerifyInt(UIDIsSame(uid_arr[0],uid_arr[1]), 0,
	"TEST3 - ISSAME FALSE FOR DIFFERENT UID'S");

	uid_arr[1].counter = 0;
	uid_arr[1].time = (time_t)-1;
	uid_arr[1].pid = 0;

	VerifyInt(UIDIsBad(uid_arr[0]), 0,
	"TEST4 - ISBAD FALSE FOR VALID UID");

	VerifyInt(UIDIsBad(uid_arr[1]), 1,
	"TEST5 - ISBAD TRUE FOR INVALID UID (TIME = -1)");

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
