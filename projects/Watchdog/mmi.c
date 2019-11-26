#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>           /* O_* constants */
#include <sys/stat.h>        /* mode constants */
#include <semaphore.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>

#include "wd.h"

#define SEM1_NAME "/is_watched"

sem_t *is_watched;

status_t MMI(const char *uargv[], const size_t interval, size_t max_intervals)
{
    struct sigaction sa1;
    pthread_t wd_thread;
    char buffer[50];

    is_watched = sem_open(SEM1_NAME, O_CREAT, 0660, 0);

    setenv("WD_ISDEAD", "1", 1);
    
    sprintf(buffer, "%s", interval);
    setenv("WD_INTERVAL", buffer, 1);

    sprintf(buffer, "%s", max_intervals);
    setenv("WD_MAXINTERVALS", buffer, 1);

    sa1.sa_handler = &ResetCounter;
    sigemptyset(&sa1.sa_mask);
    sa1.sa_flags = 0;
    sigaction(SIGUSR1, &sa1, NULL);

    wd_thread = pthread_create(&wd_thread, NULL, WDThread, uargv);
    sem_wait(is_watched);
    /* check fail */
}