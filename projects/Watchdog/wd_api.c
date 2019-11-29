#include <stdio.h>          /* printf, sprintf */
#include <stdlib.h>         /* setenv, getenv */
#include <string.h>         /* memset */

#include <fcntl.h>          /* O_* constants */
#include <semaphore.h>      /* sem_* functions */ 
#include <pthread.h>        /* pthread_create, pthread_join */

#include "wd.h"
#include "wd_shared.h"
#include "wd_thread.h"

#define SEM_NAME_IS_WATCHED "/is_watched"
#define SEM_NAME_IS_WD_READY "/is_wd_ready"
#define SEM_NAME_IS_WDT_READY "/is_wdt_ready"

sem_t *is_watched, *is_wd_ready, *is_wdt_ready;
pthread_t wd_thread;

wd_status_t MMI(const char *uargv[], const size_t interval, size_t max_intervals)
{
    struct sigaction sa1, sa2;
    char buffer[50];

    printf("MMI started\n");

    is_wd_ready = sem_open(SEM_NAME_IS_WD_READY, O_CREAT, 0666, 0);
    is_wdt_ready = sem_open(SEM_NAME_IS_WDT_READY, O_CREAT, 0666, 0);
    is_watched = sem_open(SEM_NAME_IS_WATCHED, O_CREAT, 0666, 0);

    if (NULL == getenv("WD_ISDEAD"))
    {
        sem_unlink(SEM_NAME_IS_WATCHED);
        sem_unlink(SEM_NAME_IS_WD_READY);
        sem_unlink(SEM_NAME_IS_WDT_READY);
    }

    if (NULL == getenv("WD_ISDEAD"))
    {
        // printf("MMI set WD_DEAD to 1\n");
        setenv("WD_ISDEAD", "1", 0);
    }

    sprintf(buffer, "%lu", interval);
    setenv("WD_INTERVAL", buffer, 1);

    sprintf(buffer, "%lu", max_intervals);
    setenv("WD_MAXINTERVALS", buffer, 1);

    sa1.sa_handler = &ResetCounter;
    sigemptyset(&sa1.sa_mask);
    sa1.sa_flags = 0;
    sigaction(SIGUSR1, &sa1, NULL);

    sa2.sa_handler = &DNRHandler;
    sigemptyset(&sa2.sa_mask);
    sa2.sa_flags = 0;
    sigaction(SIGUSR2, &sa2, NULL);

    wd_thread = pthread_create(&wd_thread, NULL, WDThread, uargv);

    // printf("MMI: before sem_wait(is_watched)\n");
    sem_wait(is_watched);
    // printf("MMI: after sem_wait(is_watched)\n");

    return (WD_SUCCESS);
}

void DNR(void)
{
    struct sigaction sa1, sa2;
    printf("DNR\n");
    raise(SIGUSR2);
    sem_wait(is_wd_ready);
    sem_wait(is_wdt_ready);

    memset(&sa1, 0, sizeof(struct sigaction));
    sa1.sa_flags = SA_RESETHAND;
    sa1.sa_handler = SIG_DFL;
    sigaction(SIGUSR1, &sa1, NULL);

    memset(&sa2, 0, sizeof(struct sigaction));
    sa2.sa_flags = SA_RESETHAND;
    sa2.sa_handler = SIG_DFL;
    sigaction(SIGUSR2, &sa2, NULL);

    unsetenv("WD_INTERVAL");
    unsetenv("WD_MAXINTERVALS");
    unsetenv("WD_ISDEAD");

    pthread_join(wd_thread, NULL);

    sem_unlink(SEM_NAME_IS_WATCHED);
    sem_unlink(SEM_NAME_IS_WD_READY);
    sem_unlink(SEM_NAME_IS_WDT_READY);

    sem_destroy(is_watched);
    sem_destroy(is_wd_ready);
    sem_destroy(is_wdt_ready);
}