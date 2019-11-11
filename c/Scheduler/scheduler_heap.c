#include <stdlib.h> /* malloc, free */
#include <stdio.h> /* printf */
#include <assert.h>

#include "scheduler.h"
#include "priority_q_heap.h" /* #include "priority_q.h" */
#include "task_heap.h" /* #include "task.h"" */
#include "uid.h"

struct scheduler
{
	pq_t *pq;
	int run;
};

scheduler_t *TSCreate()
{
	scheduler_t *new_scheduler = (scheduler_t *)malloc(sizeof(scheduler_t));
	
	if (NULL == new_scheduler)
	{
		return (NULL);
	}

	new_scheduler->pq = PQCreate(TaskCompare, NULL);

	if (NULL == new_scheduler->pq)
	{
		free(new_scheduler);
		new_scheduler = NULL;
		return (NULL);
	}

	new_scheduler->run = 0;

	return (new_scheduler);
}

void TSDestroy(scheduler_t *scheduler)
{
	assert(scheduler);

	TSClear(scheduler);
	PQDestroy(scheduler->pq);
	scheduler->pq = NULL;
	free(scheduler);
	scheduler = NULL;
}

int TSIsEmpty(const scheduler_t *scheduler)
{
	assert(scheduler);

	return (PQIsEmpty(scheduler->pq));
}

size_t TSSize(const scheduler_t* scheduler)
{
	assert(scheduler);

	return (PQSize(scheduler->pq));
}

/* if the op_func_t return 1 - the task is removed */
ilrd_uid_t TSAdd(scheduler_t *scheduler, size_t interval, op_func_t operation, void *param)
{
	task_t *new_task;
	int status = 0;

	assert(scheduler);

	new_task = TaskCreate(interval, operation, param);

	if (NULL == new_task)
	{
		return (bad_uid);
	}

	status = PQEnqueue(scheduler->pq, new_task);
	
	if (1 == status)
	{
		TaskDestroy(new_task);
		new_task = NULL;
		return (bad_uid);
	}

	return (TaskGetUID(new_task));
}

/* returns 0 if successful */
int TSRemove(scheduler_t *scheduler, ilrd_uid_t task_uid)
{
	task_t *task_remove = NULL;
	
	assert(scheduler);

	task_remove = PQErase(scheduler->pq, TaskMatchUID, &task_uid);

	if (task_remove)
	{
		TaskDestroy(task_remove);
		return (0);
	}
	
	return (1);
}

void TSClear(scheduler_t *scheduler)
{
	assert(scheduler);

	while (!TSIsEmpty(scheduler))
	{
		TaskDestroy(PQDequeue(scheduler->pq));
	}	
}

/* return 0 if no more tasks to run */
/* return 1 if a stop task was executd */
/* return 2 in case of error */
int TSRun(scheduler_t *scheduler)
{
	task_t* task_to_run;
	int status = 0;
	size_t time_left = 1;

	assert(scheduler);

	scheduler->run = 1;

	while(scheduler->run && !TSIsEmpty(scheduler) && 2 != status)
	{
		task_to_run = (task_t*)PQPeek(scheduler->pq);
		time_left =	TaskGetPriority(task_to_run) - time(NULL);
		while (time_left)
		{
			time_left = sleep(time_left);
		}
		PQDequeue(scheduler->pq);
		status = TaskRunOperation(task_to_run);
		switch (status)
		{
			case 0:
				{
					TaskPriorityUpdate(task_to_run);
					status = PQEnqueue(scheduler->pq, task_to_run);
					status = (status == 1) ? 2 : 0;
					status = !scheduler->run ? 1 : status;
					break;
				}
			case 1:
				{
					TaskDestroy(task_to_run);
					status = !scheduler->run ? 1 : status;
					status = TSIsEmpty(scheduler) ? 0 : status;
					break;
				}
			case 2:
				{
					TaskDestroy(task_to_run);
					break;
				}
		}
	}

	scheduler->run = 0;
	return (status);
}

void TSStop(scheduler_t *scheduler)
{
	assert(scheduler);

	scheduler->run = 0;
}
