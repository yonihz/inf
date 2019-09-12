/****************************************************************
* 																*
* FILE NAME: uid_test.c											*
* 																*
* PURPOSE: Testing UID functions								*
*                                                               *
* VERSION: 0.1													*
* 																*
* DATE: 12.09.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
* Reviewer: N/A													*
* 																*
****************************************************************/

#include <stdio.h>	/* printf */

#include "uid.h"
#include "verify_funcs.h"

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
	"TEST1 - ISSAME FOR SAME UID'S");

	VerifyInt(UIDIsSame(uid_arr[0],uid_arr[1]), 0,
	"TEST1 - ISSAME FOR DIFFERENT UID'S");
}
