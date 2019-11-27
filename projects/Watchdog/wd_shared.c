/* compile from ~/git/projects/Watchdog
gcc -c wd_shared.c ../../ds/scheduler_heap.c ../../ds/task_heap.c ../../ds/heap.c ../../ds/uid.c ../../ds/vector.c ../../ds/heapify.c ../../ds/priority_q_heap.c -I../../ds/include
*/

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
    TSAdd(sched, interval, PingFunc, &pid);
    TSAdd(sched, interval * max_intervals, ReviveFunc, &pid);

    return (sched);
}

void ResetCounter(int signum)
{
    write(0, "Reset\n", 6);
    interval_counter = 0;
}

int Ping(void *pid_to_watch)
{
    write(0, "Ping\n", 5);
    ++interval_counter;
    kill(SIGUSR1, *(pid_t*)pid_to_watch);

    return (0);
}
