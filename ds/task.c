task_t* TaskCreate(size_t interval, op_funct_t operation, const void* param)
{
    task_t new_task = malloc(sizeof(task_t));
	
	new_task.interval = interval;
	new_task.op_func = operation;
	new_task.uid = UIDCreate();
	new_task.next_time = new_task.uid.time + interval;
	new_task.param = param;

	return (new_task);
}

void TaskDestroy(task_t* task)
{
    free(task);
    task = NULL;
}

int TaskCompare(const void* data1, const void* data2, const void* param)
{
    if (*(size_t*)data1 < *(size_t*)data2)
    {
        return  (1);
    }

    return (0);
}

void TaskPriorityUpdate(task_t* task)
{

}