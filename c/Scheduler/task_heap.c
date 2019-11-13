#include <stdlib.h> /* malloc, free */
#include <assert.h>

#include "task_heap.h"

#define UNUSED(x) (void)(x)

struct task
{
	size_t interval;
    size_t next_time;
	ilrd_uid_t uid;
    const void *param;
    op_func_t op_func;
};

task_t *TaskCreate(size_t interval, op_func_t operation, void *param)
{
    task_t *new_task = (task_t *)malloc(sizeof(task_t));

    if (NULL == new_task)
    {
        return (NULL);
    }
	
	new_task->interval = interval;
	new_task->op_func = operation;
	new_task->uid = UIDCreate();
	new_task->next_time = new_task->uid.time + interval;
	new_task->param = param;

	return (new_task);
}

void TaskDestroy(task_t *task)
{
    assert(task);

    free(task);
    task = NULL;
}

/* changed return values */
int TaskCompare(const void *data1, const void *data2)
{
    if (((task_t*)data1)->next_time < ((task_t*)data2)->next_time)
    {
        return (1);
    }
    else if (((task_t*)data1)->next_time > ((task_t*)data2)->next_time)
    {
        return (-1);
    }
    else
    {
        return (0);
    }
    
}

void TaskPriorityUpdate(task_t *task)
{
    assert(task);

    task->next_time += task->interval;
}

ilrd_uid_t TaskGetUID(const task_t *task)
{
    assert(task);

    return (task->uid);
}

size_t TaskGetPriority(const task_t *task)
{
    assert(task);

    return (task->next_time);
}

int TaskRunOperation(task_t *task)
{
    assert(task);

    return (task->op_func((void*)task->param));
}

/* changed order or args */
int TaskMatchUID(const void *task_uid, const void *task)
{
    assert(task);

    return (!UIDIsSame(*(ilrd_uid_t*)task_uid, ((task_t*)task)->uid));
}
