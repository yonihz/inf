#ifndef _TASK_H_
#define _TASK_H_

#include "scheduler.h"

typedef struct task task_t;

task_t* TaskCreate(size_t interval, op_func_t operation, void* param);
void TaskDestroy(task_t* task);
int TaskCompare(const void* data1, const void* data2, const void* param);
void TaskPriorityUpdate(task_t* task);
ilrd_uid_t TaskGetUID(const task_t* task);
int TaskRunOperation(task_t* task);
size_t TaskGetPriority(const task_t* task);
int TaskMatchUID(const void* task, const void* task_uid);

#endif
