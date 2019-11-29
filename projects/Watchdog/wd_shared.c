#include <stdio.h>      /* printf */
#include <signal.h>     /* kill */
#include <stdlib.h>     /* getenv, atol */

#include "wd_shared.h"

#define UNUSED(x) (void)(x)

sig_atomic_t interval_counter = 0;
sig_atomic_t is_dnr = 0;

scheduler_t *InitScheduler(op_func_t PingFunc, op_func_t ReviveFunc, pid_t *pid_ptr, void *uargv)
{
    scheduler_t *sched = NULL;
    size_t interval = 0, max_intervals = 0;

    // printf("init sched\n");
    interval = atol(getenv("WD_INTERVAL"));
    max_intervals = atol(getenv("WD_MAXINTERVALS"));

    sched = TSCreate();
    TSAdd(sched, interval, PingFunc, pid_ptr);
    TSAdd(sched, interval * max_intervals, ReviveFunc, uargv);

    return (sched);
}

void ResetCounter(int signum)
{
    UNUSED(signum);
    interval_counter = 0;
}

void DNRHandler(int signum)
{
    UNUSED(signum);
    // write(0, "DNR HANDLER\n", 12);
    is_dnr = 1;
}

int Ping(void *pid_to_watch)
{
    if (0 != is_dnr)
    {
        // printf("DNR to %d\n", *(pid_t*)pid_to_watch);
        kill(*(pid_t*)pid_to_watch, SIGUSR2);
        return (REMOVE_TASK);
    }

    printf("Ping from %d to %d\n", getpid(),*(pid_t*)pid_to_watch);
    ++interval_counter;
    kill(*(pid_t*)pid_to_watch, SIGUSR1);

    return (CONT_SCHED);
}
