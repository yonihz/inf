#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>         /* setenv, getenv */
#include <string.h>         /* strcmp */

#include <fcntl.h>          /* O_* constants */
#include <sys/stat.h>       /* mode constants */
#include <semaphore.h>      /* sem_* functions */ 
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>

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
    struct sigaction sa1;

    sa1.sa_handler = &ResetCounter;
    sigemptyset(&sa1.sa_mask);
    sa1.sa_flags = 0;
    sigaction(SIGUSR1, &sa1, NULL);

    is_wd_ready = sem_open(SEM_NAME_IS_WD_READY, O_CREAT, 0666, 0);
    is_wdt_ready = sem_open(SEM_NAME_IS_WDT_READY, O_CREAT, 0666, 0);
    is_watched = sem_open(SEM_NAME_IS_WATCHED, O_CREAT, 0666, 0);

    if (!strcmp(getenv("WD_ISDEAD"), "1"))
    {
        CreateWD(uargv);
        printf("thread: before sem_wait(is_wd_ready)\n");
        sem_wait(is_wd_ready);
        printf("thread: after sem_wait(is_wd_ready)\n");
    }
    else
    {
        wd_pid = getppid();
    }
    

    sched = InitScheduler(Ping, ReviveWDIfDead, &wd_pid, uargv);
    sem_post(is_wdt_ready);
    printf("thread: sem_post(is_wdt_ready)\n");
    TSRun(sched);
    printf("thread: end of wd_thread\n");

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
    printf("Thread: WD counter = %d\n", interval_counter);

    if (interval_counter > atoi(getenv("WD_MAXINTERVALS")))
    {
        interval_counter = 0;
        setenv("WD_ISDEAD", "1", 1);
        CreateWD(uargv);
        sem_wait(is_wd_ready);
        sem_post(is_wdt_ready);
    }

    return (WD_SUCCESS);
}


