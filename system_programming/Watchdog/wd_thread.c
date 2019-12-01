#include <stdio.h>          /* printf */
#include <stdlib.h>         /* setenv, getenv */
#include <string.h>         /* strcmp */

#include <fcntl.h>          /* O_* constants */
#include <semaphore.h>      /* sem_* functions */ 

#include "wd.h"
#include "wd_shared.h"

static pid_t wd_pid = 0;

int ReviveWDIfDead(void *uargv);
int CreateWD(void *uargv);
void *WDThread(void *uargv);

void *WDThread(void *uargv)
{
    scheduler_t *sched = NULL;
    struct sigaction sa_sigusr1, sa_sigusr2;

    InitSigHandler(SIGUSR1, &ResetCounter, &sa_sigusr1);
    InitSigHandler(SIGUSR2, &DNRHandler, &sa_sigusr2);

    InitSem();

    if (!strcmp(getenv("WD_ISDEAD"), "1"))
    {
        CreateWD(uargv);
        sem_wait(is_wd_ready);
    }
    else
    {
        wd_pid = getppid();
    }
    

    sched = InitScheduler(Ping, ReviveWDIfDead, &wd_pid, uargv);
    sem_post(is_wdt_ready);
    TSRun(sched);

    TSDestroy(sched);    
    sem_post(is_wdt_ready);

    return (NULL);
}

int CreateWD(void *uargv)
{
    setenv("WD_ISDEAD", "0", 1);
    wd_pid = fork();

    if (wd_pid == 0) /* child - watchdog process */
    {
        execv(WD_PATH, (char**)uargv);
    }

    if (wd_pid < 0) /* parent - user process */
    {
        return (WD_FAILURE);
    }

    return (WD_SUCCESS);
}

int ReviveWDIfDead(void *uargv)
{
    printf("Thread counter = %d\n", interval_counter);

    if (interval_counter >= atoi(getenv("WD_MAXINTERVALS")))
    {
        printf("Reviving WD\n");
        interval_counter = 0;
        setenv("WD_ISDEAD", "1", 1);
        CreateWD(uargv);
        sem_wait(is_wd_ready);
        sem_post(is_wdt_ready);
    }

    return (WD_SUCCESS);
}


