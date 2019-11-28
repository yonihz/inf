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

#include "wd.h"
#include "wd_app.h"
#include "wd_shared.h"

#define SEM_NAME_IS_WATCHED "/is_watched"
#define SEM_NAME_IS_WD_READY "/is_wd_ready"
#define SEM_NAME_IS_WDT_READY "/is_wdt_ready"

sem_t *is_watched, *is_wd_ready, *is_wdt_ready;
pid_t uapp_pid;

int main (int argc, char *argv[])
{
    scheduler_t *sched = NULL;
    struct sigaction sa1;

    sa1.sa_handler = &ResetCounter;
    sigemptyset(&sa1.sa_mask);
    sa1.sa_flags = 0;
    sigaction(SIGUSR1, &sa1, NULL);

    is_wd_ready = sem_open(SEM_NAME_IS_WD_READY, O_CREAT);
    is_wdt_ready = sem_open(SEM_NAME_IS_WDT_READY, O_CREAT);
    is_watched = sem_open(SEM_NAME_IS_WATCHED, O_CREAT);

    sched = InitScheduler(Ping, ReviveUAppIfDead, uapp_pid);

    sem_post(is_wdt_ready);
    sem_wait(is_wd_ready);
    sem_post(is_watched);

    TSRun(sched);

    return 0;
}

int CreateUApp(char const **uargv)
{
    uapp_pid = fork();

    if (uapp_pid == 0) /* child - revived user process */
    {
        execv((char * const)uargv, (char * const*)(uargv + 1));
    }
    else if (uapp_pid > 0) /* parent - watchdog process */
    {
        return (WD_SUCCESS);
    }
    else
    {
        return (WD_FAILURE);
    }

    return (WD_SUCCESS);
}

int ReviveUAppIfDead(void *uargv)
{
    if (intervals_counter == atoi(getenv("WD_MAXINTERVALS")))
    {
        intervals_counter = 0;
        is_wd_ready = sem_open(SEM_NAME_IS_WD_READY, O_CREAT);
        is_wdt_ready = sem_open(SEM_NAME_IS_WDT_READY, O_CREAT);
        CreateUApp((char const **)(uargv) + 1);
        sem_wait(is_wdt_ready);
        sem_post(is_watched);
    }

    return (WD_SUCCESS);
}
    