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

#include "wd_shared.h"

#define SEM1_NAME "/is_watched"

sem_t *is_watched;

int WDThread(const char **argv, size_t interval, size_t max_intervals)
{
    TaskCreate(interval, Ping())
    InitScheduler()
    if (atoi(getenv(WD_ISDEAD) == 1)
    {
        CreateWD();

    }
}