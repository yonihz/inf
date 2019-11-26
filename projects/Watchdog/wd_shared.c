#include <signal.h>

#include "scheduler.h"
#include "task.h"

sig_atomic_t counter = 0;

scheduler_t *InitScheduler(task_t *PingTask, task_t *ReviveTask, size_t interval, size_t max_intervals)
{
    scheduler_t *sched = TSCreate();
    /* check fail */
    TaskCreate(interval, PingTask, NULL);
    TaskCreate(interval * max_intervals, ReviveTask, NULL);
}

void ResetCounter(int signum)
{
    counter = 0;
}

int Ping(void *pid)
{
    ++counter;
    kill(SIGUSR1, *(pid_t*)pid);
}
