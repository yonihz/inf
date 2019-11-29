#include <stdio.h>          /* printf */
#include <stdlib.h>         /* setenv, getenv */
#include <string.h>         /* strcmp */

#include <fcntl.h>          /* O_* constants */
#include <semaphore.h>      /* sem_* functions */ 

#include "wd.h"
#include "wd_shared.h"
#include "wd_thread.h"

#define SEM_NAME_IS_WATCHED "/is_watched"
#define SEM_NAME_IS_WD_READY "/is_wd_ready"
#define SEM_NAME_IS_WDT_READY "/is_wdt_ready"

sem_t *is_watched, *is_wd_ready, *is_wdt_ready;
pid_t wd_pid = 0;

void *WDThread(void *uargv)
{
    scheduler_t *sched = NULL;
    struct sigaction sa1, sa2;

    sa1.sa_handler = &ResetCounter;
    sigemptyset(&sa1.sa_mask);
    sa1.sa_flags = 0;
    sigaction(SIGUSR1, &sa1, NULL);

    sa2.sa_handler = &DNRHandler;
    sigemptyset(&sa2.sa_mask);
    sa2.sa_flags = 0;
    sigaction(SIGUSR2, &sa2, NULL);

    is_wd_ready = sem_open(SEM_NAME_IS_WD_READY, O_CREAT, 0666, 0);
    is_wdt_ready = sem_open(SEM_NAME_IS_WDT_READY, O_CREAT, 0666, 0);
    is_watched = sem_open(SEM_NAME_IS_WATCHED, O_CREAT, 0666, 0);

    if (!strcmp(getenv("WD_ISDEAD"), "1"))
    {
        CreateWD(uargv);
        // printf("thread: before sem_wait(is_wd_ready)\n");
        sem_wait(is_wd_ready);
        // printf("thread: after sem_wait(is_wd_ready)\n");
    }
    else
    {
        // printf("uapp: wd pid is %d\n", getppid());
        wd_pid = getppid();
    }
    

    sched = InitScheduler(Ping, ReviveWDIfDead, &wd_pid, uargv);
    // printf("thread: sem_post(is_wdt_ready)\n");
    sem_post(is_wdt_ready);
    TSRun(sched);
    TSDestroy(sched);    
    // printf("thread sched finished\n");
    sem_post(is_wdt_ready);
    // printf("thread end\n");
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
    else if (wd_pid > 0) /* parent - user process */
    {
        return (WD_SUCCESS);
    }
    else
    {
        return (WD_FAILURE);
    }

    return (WD_SUCCESS);
}

int ReviveWDIfDead(void *uargv)
{
    // printf("Thread: WD counter = %d\n", interval_counter);

    if (0 != is_dnr)
    {
        return (REMOVE_TASK);
    }

    if (interval_counter >= atoi(getenv("WD_MAXINTERVALS")))
    {
        printf("revive wd\n");
        interval_counter = 0;
        setenv("WD_ISDEAD", "1", 1);
        CreateWD(uargv);
        // printf("revive wd: before sem_wait(is_wd_ready)\n");
        sem_wait(is_wd_ready);
        // printf("revive wd: after sem_wait(is_wd_ready)\n");
        // printf("revive wd: sem_post(is_wdt_ready)\n");
        sem_post(is_wdt_ready);
    }

    return (WD_SUCCESS);
}


