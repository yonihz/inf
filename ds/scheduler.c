#include <stdlib.h> /* malloc, free */
#include <stdio.h> /* printf */

#include "scheduler.h"
#include "priority_q.h"
#include "task.h"

struct scheduler
{
	pq_t* pq;
	int run;
};

scheduler_t* TSCreate()
{
	scheduler_t* new_scheduler = malloc(sizeof(scheduler_t));
	
	if (NULL == new_scheduler)
	{
		return (NULL);
	}

	new_scheduler->pq = PQCreate(TaskCompare, NULL);
	new_scheduler->run = 0;

	return (new_scheduler);
}

void TSDestroy(scheduler_t* scheduler)
{
	TSClear(scheduler);
	PQDestroy(scheduler->pq);
	scheduler->pq = NULL;
	free(scheduler);
	scheduler = NULL;
}

int TSIsEmpty(const scheduler_t* scheduler)
{
	return (PQIsEmpty(scheduler->pq));
}

size_t TSSize(const scheduler_t* scheduler)
{
	return (PQSize(scheduler->pq));
}

/* if the op_func_t return 1 - the task is removed */
ilrd_uid_t TSAdd(scheduler_t* scheduler, size_t interval, op_func_t operation, void* param)
{
	task_t* new_task;
	new_task = TaskCreate(interval, operation, param);
	PQEnqueue(scheduler->pq, new_task);
	return (TaskGetUID(new_task));
}

/* returns 0 if successful */
int TSRemove(scheduler_t* scheduler, ilrd_uid_t task_uid)
{
	task_t* task_remove = PQErase(scheduler->pq, TaskMatchUID, (void*)&task_uid);
	
	if (task_remove)
	{
		TaskDestroy(task_remove);
		return (0);
	}
	
	return (1);
}

void TSClear(scheduler_t* scheduler)
{
	while (!TSIsEmpty(scheduler))
	{
		free(PQDequeue(scheduler->pq));
	}	
}

/* return 0 if no more tasks to run */
/* return 1 if a stop task was executd */
/* return 2 in case of error */
int TSRun(scheduler_t* scheduler)
{
	task_t* task_to_run;
	int status = 0;
	scheduler->run = 1;

	while(scheduler->run && !TSIsEmpty(scheduler) && 2 != status)
	{
		task_to_run = (task_t*)PQPeek(scheduler->pq);
		sleep(TaskGetPriority(task_to_run) - time(NULL));
		PQDequeue(scheduler->pq);
		status = TaskRunOperation(task_to_run);
		if (1 == status || 2 == status)
		{
			TaskDestroy(task_to_run);
			continue;
		}
		TaskPriorityUpdate(task_to_run);
		PQEnqueue(scheduler->pq, (void*)task_to_run);
	}

#ifndef NDEBUG
	if (2 == status)
	{
		printf("Scheduler stopped - operation failed \n");
	}

	if (!scheduler->run)
	{
		printf("Scheduler stopped by user \n");
	}

	if (TSIsEmpty(scheduler))
	{
		printf("Scheduler stopped - No more tasks to run\n");
	}
#endif

	if (TSIsEmpty(scheduler))
	{
		status = 0;
	}

	if (!scheduler->run)
	{
		status = 1;
	}

	scheduler->run = 0;
	return (status);
}

void TSStop(scheduler_t* scheduler)
{
	scheduler->run = 0;
}
