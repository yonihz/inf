#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>           /* O_* constants */
#include <sys/stat.h>        /* mode constants */
#include <semaphore.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h> /* kill */

#define SEM_NAME_ISWATCHED "/is_watched"
#define SEM_NAME_WD_ISREADY "/wd_isread"
#define SEM_NAME_WDT_ISREADY "/wtd_isready"

sem_t *is_watched;

int main (int argc, char *argv[])
{

}

/* recode */
int CreateUApp(const char **uargv)
{
    setenv("WD_ISDEAD", "0", 1);
    pid = fork();

    if (pid == 0) /* child - watchdog process */
    {
        execv(WD_PATH, uargv);
    }
    else if (pid > 0) /* parent - user process */
    {
        return (WD_SUCCESS); /* returns watchdog pid */
    }
    else
    {
        return (WD_FAILURE);
    }
}

/* recode */
int ReviveUAppIfDead(const char **uargv)
{
    if (counter == atoi(getenv("WD_MAXINTERVALS")))
    {
        counter = 0;
        is_wd_ready = sem_open(SEM_NAME_IS_WD_READY, O_CREAT);
        is_wdt_ready = sem_open(SEM_NAME_IS_WDT_READY, O_CREAT);
        setenv("WD_ISDEAD", "1", 1);
        CreateWD(uargv);
        sem_wait(is_wd_ready);
        sem_wait(is_wdt_ready);
    }
}
    