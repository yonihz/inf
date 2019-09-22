/****************************************************************
* 																*
* FILE NAME: scheduler_test.c									*
* 																*
* PURPOSE: Testing scheduler functions				    		*
*                                                               *
* VERSION: 0.1													*
* 																*
* DATE: 19.09.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
* Reviewer: N/A													*
* 																*
****************************************************************/

/*
gd -Iinclude uid.c dlist.c sorted_list.c priority_q.c task.c scheduler.c test/scheduler_test.c test/verify_funcs.c
*/

/*
op_func return: 0 - continue, 1 - task does not return to queue and destroyed, 2 - stop
*/


#include <stdio.h>	/* printf */

#include "scheduler.h"
#include "verify_funcs.h"

#define UNUSED(x) (void)(x)

/* API test functions */

int int_compare(const void* data1, const void* data2, const void* param);
int int_is_smaller(const void* data1, const void* data2, const void* param);
int isNum(const void* data, const void* param);

int PrintString(const void* str);
int AddTaskAtRun(const void* task);
int TSRemoveAtRun(const void* task);
int TSClearAtRun(const void* task);
int TSStopAtRun(const void* task);

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

    task_user_t task_user1 = {NULL, 0, NULL, NULL, {0, 0, 0}};
    task_user_t task_user2 = {NULL, 0, NULL, NULL, {0, 0, 0}};
    task_user_t task_user3 = {NULL, 0, NULL, NULL, {0, 0, 0}};

    task_user1.interval = 7;
    task_user1.scheduler = scheduler1;
    task_user1.param = "new task with 7sec interval";
    task_user1.op_func = PrintString;

    task_uid[0] = TSAdd(scheduler1, 5, PrintString, "task with 5sec interval");
    task_uid[1] = TSAdd(scheduler1, 6, PrintString, "task with 6sec interval");
    task_uid[2] = TSAdd(scheduler1, 7, AddTaskAtRun, &task_user1);


    task_user2.scheduler = scheduler1;
    task_user2.uid = task_uid[0];

    task_uid[3] = TSAdd(scheduler1, 13, TSRemoveAtRun, &task_user2);

    task_user3.scheduler = scheduler1;
    task_uid[4] = TSAdd(scheduler1, 60, TSStopAtRun, &task_user3);
    task_uid[5] = TSAdd(scheduler1, 70, TSClearAtRun, &task_user3);

    printf("Size: %lu\n",TSSize(scheduler1));

    TSRun(scheduler1);
    printf("Size: %lu\n",TSSize(scheduler1));
    TSRun(scheduler1);
    printf("Size: %lu\n",TSSize(scheduler1));

    TSDestroy(scheduler1);
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

int PrintString(const void* str)
{
    printf("%s\n",(char*)str);
    return (0);
}

int AddTaskAtRun(const void* task)
{
    task_user_t* task_add = (task_user_t*)task;
    printf("Added task at run\n");
    TSAdd(task_add->scheduler, task_add->interval, task_add->op_func, (void*)(task_add->param));
    return (1);
}

int TSRemoveAtRun(const void* task)
{
    task_user_t* task_remove = (task_user_t*)task;
    printf("Removed task at run\n");
    TSRemove(task_remove->scheduler, task_remove->uid);
    return (1);
}

int TSClearAtRun(const void* task)
{
    task_user_t* task_clear = (task_user_t*)task;
    printf("Clear\n");
    TSClear(task_clear->scheduler);
    return (1);
}

int TSStopAtRun(const void* task)
{
    task_user_t* task_stop = (task_user_t*)task;
    printf("Stop task\n");
    TSStop(task_stop->scheduler);
    return (1);
}