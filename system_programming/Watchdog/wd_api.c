#include <stdio.h>          /* printf, sprintf */
#include <stdlib.h>         /* setenv, getenv */

#include <pthread.h>        /* pthread_create, pthread_join */

#include "wd.h"
#include "wd_shared.h"

static pthread_t wd_thread;

extern void *WDThread(void *uargv);

wd_status_t MMI(const char *uargv[], const size_t interval, size_t max_intervals)
{
    struct sigaction sa_sigusr1, sa_sigusr2;
    char buffer[50];

    printf("MMI started\n");

    InitSem();

    setenv("WD_ISDEAD", "1", 0);

    sprintf(buffer, "%lu", interval);
    setenv("WD_INTERVAL", buffer, 1);

    sprintf(buffer, "%lu", max_intervals);
    setenv("WD_MAXINTERVALS", buffer, 1);

    InitSigHandler(SIGUSR1, &ResetCounter, &sa_sigusr1);
    InitSigHandler(SIGUSR2, &DNRHandler, &sa_sigusr2);

    if ((wd_thread = pthread_create(&wd_thread, NULL, WDThread, uargv)))
    {
        perror("pthread_create failed");
        exit(1); 
    }

    sem_wait(is_watched);

    return (WD_SUCCESS);
}

void DNR(void)
{
    struct sigaction sa_sigusr1, sa_sigusr2;
    
    printf("DNR started\n");

    raise(SIGUSR2);
    sem_wait(is_wd_ready);
    sem_wait(is_wdt_ready);

    ResetSigHandler(SIGUSR1, &sa_sigusr1);
    ResetSigHandler(SIGUSR2, &sa_sigusr2);

    unsetenv("WD_INTERVAL");
    unsetenv("WD_MAXINTERVALS");
    unsetenv("WD_ISDEAD");

    pthread_join(wd_thread, NULL);

    /*
    if (pthread_join(wd_thread, NULL))
    {
        perror("pthread_join failed");
        exit(1);   
    }
    */

    sem_unlink(SEM_NAME_IS_WATCHED);
    sem_unlink(SEM_NAME_IS_WD_READY);
    sem_unlink(SEM_NAME_IS_WDT_READY);
}