/****************************************************************
* 																*
* FILE NAME: scheduler_test.c									*
* 																*
* PURPOSE: Testing scheduler functions				    		*
*                                                               *
* DATE: 19.09.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
****************************************************************/

/* heap implementation:
gd scheduler_heap.c scheduler_test.c task_heap.c ../../ds/heap.c ../../ds/uid.c ../../ds/vector.c ../../ds/heapify.c ../../ds/priority_q_heap.c -I../../ds/include
*/

#include <stdio.h>	/* printf */
#include <string.h>	/* strcmp */

#include "scheduler.h"

#define UNUSED(x) (void)(x)

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define MAG  "\x1B[35m"
#define RESET "\x1B[0m"

void VerifyInt(int test, int expected, char test_name[]);
void VerifySizet(size_t test,size_t expected, char test_name[]);
void VerifyVoidptr(void* test, void* expected, char test_name[]);
void VerifyChar(char test[], char expected[], char test_name[]);
void VerifyStrncmp(char test[], char expected[], size_t n, char test_name[]);

/* API test functions */

int PrintString(void* str);
int AddTaskAtRun(void* task);
int TSRemoveAtRun(void* task);
int TSClearAtRun(void* task);
int TSStopAtRun(void* task);

void TestBasic();

struct task_user
{
    scheduler_t* scheduler;
	size_t interval;
    op_func_t op_func;
    const void* param;
    ilrd_uid_t uid;
};

typedef struct task_user task_user_t;

int main()
{
	TestBasic();
	return (0);
}

/* Test functions for API */

void TestBasic()
{
    scheduler_t* scheduler1 = TSCreate();
    ilrd_uid_t task_uid[20];
    int status = 0;

    task_user_t task_user1 = {NULL, 0, NULL, NULL, {0, 0, 0}};
    task_user_t task_user2 = {NULL, 0, NULL, NULL, {0, 0, 0}};
    task_user_t task_user3 = {NULL, 0, NULL, NULL, {0, 0, 0}};

    printf("Task scheduler tests\n");

    task_user1.interval = 6;
    task_user1.scheduler = scheduler1;
    task_user1.param = "TASK3: print with 6sec interval";
    task_user1.op_func = PrintString;

    task_uid[0] = TSAdd(scheduler1, 5, PrintString, "TASK1: print with 5sec interval");
    task_uid[1] = TSAdd(scheduler1, 7, PrintString, "TASK2: print with 7sec interval");
    task_uid[2] = TSAdd(scheduler1, 12, AddTaskAtRun, &task_user1);

    task_user2.scheduler = scheduler1;
    task_user2.uid = task_uid[1];

    task_uid[3] = TSAdd(scheduler1, 16, TSRemoveAtRun, &task_user2);

    task_user3.scheduler = scheduler1;
    task_uid[4] = TSAdd(scheduler1, 30, TSStopAtRun, &task_user3);
    task_uid[5] = TSAdd(scheduler1, 40, TSClearAtRun, &task_user3);

    VerifySizet(TSSize(scheduler1), 6, 
    "SIZE IS 6 BEFORE RUN");
    VerifyInt(TSIsEmpty(scheduler1), 0, 
    "ISEMPTY IS FALSE BEFORE RUN");

    status = TSRun(scheduler1);
    VerifyInt(status, 1,
    "RUN RETURNED 1 AFTER STOP");
    VerifySizet(TSSize(scheduler1), 3, 
    "SIZE IS 3 AFTER STOP");
    status = TSRun(scheduler1);
    VerifyInt(status, 0,
    "RUN RETURNED 0 AFTER CLEAR");
    VerifySizet(TSSize(scheduler1), 0, 
    "SIZE IS 0 AFTER CLEAR");
    VerifyInt(TSIsEmpty(scheduler1), 1, 
    "ISEMPTY IS TRUE AFTER CLEAR");

    TSDestroy(scheduler1);
}

int PrintString(void* str)
{
    printf("%s\n",(char*)str);
    return (0);
}

int AddTaskAtRun(void* task)
{
    task_user_t* task_add = (task_user_t*)task;
    printf(MAG), printf("TSADD TASK3 - CHECK IF ADDED\n"), printf(RESET);
    TSAdd(task_add->scheduler, task_add->interval, task_add->op_func, (void*)(task_add->param));
    return (1);
}

int TSRemoveAtRun(void* task)
{
    int status = 1;
    task_user_t* task_remove = (task_user_t*)task;
    printf(MAG), printf("TSREMOVE TASK2 - CHECK IF REMOVED\n"), printf(RESET);
    status = TSRemove(task_remove->scheduler, task_remove->uid);
    if (status)
    {
        return (2);
    }
    return (1);
}

int TSClearAtRun(void* task)
{
    task_user_t* task_clear = (task_user_t*)task;
    printf(MAG), printf("TSCLEAR\n"), printf(RESET);
    TSClear(task_clear->scheduler);
    return (1);
}

int TSStopAtRun(void* task)
{
    task_user_t* task_stop = (task_user_t*)task;
    printf(MAG), printf("TSSTOP\n"), printf(RESET);
    TSStop(task_stop->scheduler);
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
