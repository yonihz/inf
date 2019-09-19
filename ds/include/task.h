#ifndef _TASK_H_
#define _TASK_H_

#include "uid.h"
#include "scheduler.h"

typedef struct task
{
	ilrd_uid_t uid;
	size_t interval;
	size_t next_run;
	op_func_t operation;
	const void* param;
} task_t;

task_t* TaskCreate(size_t interval, op_funct_t operation, const void* param);
void TaskDestroy(task_t* task);
int TaskCompare(const void* data1, const void* data2, const void* param);
void TaskPriorityUpdate(task_t* task);
ilrd_uid_t TaskGetUID(task_t* task);


#endif
