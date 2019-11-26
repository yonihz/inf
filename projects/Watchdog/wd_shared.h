#ifndef _WD_SHARED_H_
#define _WD_SHARED_H_

#include "scheduler.h"
#include "task.h"

scheduler_t *InitScheduler(task_t *PingTask, task_t *ReviveTask, size_t interval, size_t max_intervals);

void ResetCounter(int signum);

int Ping(void *pid);

#endif /* _WD_SHARED_H_ */