#include <stdlib.h> /* malloc, free */

#include "task.h"
#include "uid.h"

#define UNUSED(x) (void)(x)

struct task
{
	size_t interval;
    size_t next_time;
	ilrd_uid_t uid;
    const void* param;
    op_func_t op_func;
};

task_t* TaskCreate(size_t interval, op_func_t operation, void* param)
{
    task_t* new_task = malloc(sizeof(task_t));
	
	new_task->interval = interval;
	new_task->op_func = operation;
	new_task->uid = UIDCreate();
	new_task->next_time = new_task->uid.time + interval;
	new_task->param = param;

	return (new_task);
}

void TaskDestroy(task_t* task)
{
    free(task);
    task = NULL;
}

int TaskCompare(const void* data1, const void* data2, const void* param)
{
    UNUSED(param);

    if (((task_t*)data1)->next_time < ((task_t*)data2)->next_time)
    {
        return  (1);
    }

    return (0);
}

void TaskPriorityUpdate(task_t* task)
{
    task->next_time += task->interval;
}

ilrd_uid_t TaskGetUID(const task_t* task)
{
    return (task->uid);
}

size_t TaskGetPriority(const task_t* task)
{
    return (task->next_time);
}

int TaskRunOperation(task_t* task)
{
    return (task->op_func((void*)task->param));
}

int TaskMatchUID(const void* task, const void* task_uid)
{
    return (!UIDIsSame(((task_t*)task)->uid, *(ilrd_uid_t*)task_uid));
}
