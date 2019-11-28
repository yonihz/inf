#include <unistd.h>
#include <stdio.h>          /* sprintf */
#include <stdlib.h>         /* setenv, getenv */

#include <fcntl.h>          /* O_* constants */
#include <sys/stat.h>       /* mode constants */
#include <semaphore.h>      /* sem_* functions */ 
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>         /* sigaction */
#include <pthread.h>        /* pthread_create */

#include "wd.h"
#include "wd_shared.h"
#include "wd_thread.h"

#define SEM_NAME_IS_WATCHED "/is_watched"

sem_t *is_watched;

wd_status_t MMI(const char *uargv[], const size_t interval, size_t max_intervals)
{
    struct sigaction sa1;
    pthread_t wd_thread;
    char buffer[50];

    is_watched = sem_open(SEM_NAME_IS_WATCHED, O_CREAT, 0660, 0);

    setenv("WD_ISDEAD", "1", 1);
    
    sprintf(buffer, "%lu", interval);
    setenv("WD_INTERVAL", buffer, 1);

    sprintf(buffer, "%lu", max_intervals);
    setenv("WD_MAXINTERVALS", buffer, 1);

    sa1.sa_handler = &ResetCounter;
    sigemptyset(&sa1.sa_mask);
    sa1.sa_flags = 0;
    sigaction(SIGUSR1, &sa1, NULL);

    wd_thread = pthread_create(&wd_thread, NULL, WDThread, uargv);
    sem_wait(is_watched);
    /* check fail */

    return (WD_SUCCESS);
}

void DNR(void)
{
    /* code */
}