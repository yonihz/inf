#include <stdio.h>      /* printf */
#include <signal.h>     /* kill */
#include <stdlib.h>     /* getenv, atol */
#include <string.h>     /* memset */

#include "wd_shared.h"

#define UNUSED(x) (void)(x)

sig_atomic_t interval_counter = 0, is_dnr = 0;

sem_t *is_watched, *is_wd_ready, *is_wdt_ready;

scheduler_t *InitScheduler(op_func_t PingFunc, op_func_t ReviveFunc, pid_t *pid_ptr, void *uargv)
{
    scheduler_t *sched = NULL;
    size_t interval = 0, max_intervals = 0;

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
    is_dnr = 1;
}

int Ping(void *pid_to_watch)
{
    if (0 != is_dnr)
    {
        kill(*(pid_t*)pid_to_watch, SIGUSR2);
        return (STOP_SCHED);
    }

    printf("Ping from %d to %d\n", getpid(),*(pid_t*)pid_to_watch);
    ++interval_counter;
    kill(*(pid_t*)pid_to_watch, SIGUSR1);

    return (CONT_SCHED);
}

void InitSigHandler(int signum, sa_handler_t handler, sigaction_t *sa)
{
    sa->sa_handler = handler;
    sigemptyset(&(sa->sa_mask));
    sa->sa_flags = 0;
    
    if (sigaction(signum, sa, NULL) == -1)
    {
        perror("sigaction failed");
        exit(1); 
    }
}

void ResetSigHandler(int signum, sigaction_t *sa)
{
    memset(sa, 0, sizeof(struct sigaction));
    sa->sa_flags = SA_RESETHAND;
    sa->sa_handler = SIG_DFL;

    if (sigaction(signum, sa, NULL) == -1)
    {
        perror("sigaction failed");
        exit(1); 
    }
}

void InitSem(void)
{
    if ((is_wd_ready = sem_open(SEM_NAME_IS_WD_READY, O_CREAT, 0666, 0)) == SEM_FAILED) 
    {
        perror("Semaphore is_wd_ready init failed");
        exit(1);
    }

    if ((is_wdt_ready = sem_open(SEM_NAME_IS_WDT_READY, O_CREAT, 0666, 0)) == SEM_FAILED) 
    {
        perror("Semaphore is_wdt_ready init failed");
        exit(1);
    }

    if ((is_watched = sem_open(SEM_NAME_IS_WATCHED, O_CREAT, 0666, 0)) == SEM_FAILED) 
    {
        perror("Semaphore is_watched init failed");
        exit(1);
    }
}
