#include "scheduler.h"
#include "priority_q.h"
#include "task.h"

struct scheduler
{
	pq_t pq;
	int run;
}

scheduler_t* TSCreate();
{
	scheduler_t new_scheduler = malloc(sizeof(scheduler_t));
	
	if (NULL = new_scheduler)
	{
		return (NULL);
	}

	new_scheduler->pq = PQCreate(TaskCompare, NULL);
	new_scheduler->run = 0;

	return (new_scheduler);
}

void TSDestroy(scheduler_t* scheduler)
{
	PQDestroy(scheduler->pq);
	scheduler->pq = NULL;
	free(scheduler);
	scheduler = NULL;
}

int TSIsEmpty(const scheduler_t* scheduler);
{
	return (PQIsEmpty(scheduler->pq));
}

size_t TSSize(const scheduler_t* scheduler);
{
	return (PQSize(scheduler->pq));
}

/* if the op_func_t return 1 - the task is removed */
ilrd_uid_t TSAdd(scheduler_t* scheduler, size_t interval, op_func_t operation, const void* param);
{
	task_t new_task;
	new_task = TaskCreate(interval, operation, param);
	PQEnqueue(scheduler->pq, new_task);
	return (TaskGetUID(new_task));
}

/* returns 0 if successful */
int TSRemove(scheduler_t* scheduler, ilrd_uid_t task_uid)
{
	task_t task_remove = PQErase(scheduler->pq, match_uid);
	if (task_remove)
	{
		TaskDestroy(task_remove);
		return (0);
	}
	
	return (1);
}

void TSClear(scheduler_t* scheduler);
{
	PQClear(scheduler->pq);	
}

/* return 0 if no more tasks to run */
/* return 1 if a stop task was executd */
/* return 2 in case of error */
int TSRun(scheduler_t* scheduler)
{
	task_t* task_to_run;
	scheduler.run = 1;
	int status = 0;

	while(scheduler.run && !TSIsEmpty(scheduler))
	{
		task_to_run = (task_t*)PQPeek(scheduler->pq);
		sleep(TaskGetNextTime(task_to_run) - time(NULL));
		PQDEqueue(scheduler);
		status = TaskRunOperation(task_to_run);
		TaskPriorityUpdate(task_to_run);

		if (1 == status)
		{
			return (2);
		}
	}
}

void TSStop(scheduler_t* scheduler);
