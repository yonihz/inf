#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>         /* setenv, getenv */

#include <fcntl.h>          /* O_* constants */
#include <sys/stat.h>       /* mode constants */
#include <semaphore.h>      /* sem_* functions */ 
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>

#include "wd_shared.h"
#include "wd_thread.h"

#define SEM_NAME_IS_WATCHED "/is_watched"
#define SEM_NAME_IS_WD_READY "/is_wd_ready"
#define SEM_NAME_IS_WDT_READY "/is_wdt_ready"

sem_t *is_watched, *is_wd_ready, *is_wdt_ready;
pid_t pid;

int WDThread(const char **uargv)
{
    scheduler_t *sched = NULL;
 
    if (strcmp(getenv("WD_ISDEAD"), "1"))
    {
        CreateWD(uargv);
        sem_wait(is_wd_ready);
    }

    sched = InitScheduler(Ping, ReviveWDIfDead);
    sem_post(is_wdt_ready);
    TSRun(sched);
}

int CreateWD(const char **uargv)
{
    setenv("WD_ISDEAD", "0", 1);
    pid = fork();

    if (pid == 0) /* child - watchdog process */
    {
        execv(WD_PATH, uargv);
    }
    else if (pid > 0) /* parent - user process */
    {
        return (WD_SUCCESS); /* returns watchdog pid */
    }
    else
    {
        return (WD_FAILURE);
    }
}

int ReviveWDIfDead(const char **uargv)
{
    if (counter == atoi(getenv("WD_MAXINTERVALS")))
    {
        counter = 0;
        is_wd_ready = sem_open(SEM_NAME_IS_WD_READY, O_CREAT);
        is_wdt_ready = sem_open(SEM_NAME_IS_WDT_READY, O_CREAT);
        setenv("WD_ISDEAD", "1", 1);
        CreateWD(uargv);
        sem_wait(is_wd_ready);
        sem_wait(is_wdt_ready);
    }
}


