#include <stdio.h>          /* printf */
#include <stdlib.h>         /* setenv, getenv */

#include <fcntl.h>          /* O_* constants */
#include <semaphore.h>      /* sem_* functions */ 

#include "wd.h"
#include "wd_shared.h"

#define UNUSED(x) (void)(x)

sem_t *is_watched, *is_wd_ready, *is_wdt_ready;
pid_t uapp_pid = 0;

int CreateUApp(void *uargv);
int ReviveUAppIfDead(void *uargv);

int main (int argc, char *argv[])
{
    scheduler_t *sched = NULL;
    struct sigaction sa_sigusr1, sa_sigusr2;

    UNUSED(argc);

    printf("WD started\n");

    InitSigHandler(SIGUSR1, &ResetCounter, &sa_sigusr1);
    InitSigHandler(SIGUSR2, &DNRHandler, &sa_sigusr2);

    InitSem();

    uapp_pid = getppid();

    /* argv[0]: user program path, argv[1]: user program's argv */ 
    sched = InitScheduler(Ping, ReviveUAppIfDead, &uapp_pid, argv);

    sem_post(is_wd_ready);
    sem_wait(is_wdt_ready);
    sem_post(is_watched);

    TSRun(sched);
    TSDestroy(sched);
    sem_post(is_wd_ready);

    return 0;
}

int CreateUApp(void *uargv)
{
    uapp_pid = fork();

    if (uapp_pid == 0) /* child - revived user process */
    {
        execv(*(char **)uargv, (char **)uargv);
    }
    
    if (uapp_pid < 0) /* parent - watchdog process */
    {
        return (WD_FAILURE);
    }

    return (WD_SUCCESS);
}

int ReviveUAppIfDead(void *uargv)
{
    printf("WD counter = %d\n", interval_counter);

    if (interval_counter >= atoi(getenv("WD_MAXINTERVALS")))
    {
        interval_counter = 0;
        printf("Reviving user app: %s\n", *(char **)uargv);
        CreateUApp(uargv);
        sem_wait(is_wdt_ready);
        sem_post(is_watched);
    }

    return (WD_SUCCESS);
}
    