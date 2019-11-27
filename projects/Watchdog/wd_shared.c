#include <signal.h>
#include <stdlib.h>

#include "wd_shared.h"

sig_atomic_t interval_counter = 0;

scheduler_t *InitScheduler(op_func_t PingFunc, op_func_t ReviveFunc, pid_t pid)
{
    scheduler_t *sched = NULL;
    size_t interval = 0, max_intervals = 0;

    interval = atol(getenv("WD_INTERVAL"));
    max_intervals = atol(getenv("WD_MAXINTERVALS"));

    sched = TSCreate();
    TSAdd(sched, interval, PingFunc, pid);
    TSAdd(sched, interval * max_intervals, ReviveFunc, pid);
}

void ResetCounter(int signum)
{
    interval_counter = 0;
}

int Ping(void *pid_to_watch)
{
    ++interval_counter;
    kill(SIGUSR1, *(pid_t*)pid_to_watch);
}
