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
