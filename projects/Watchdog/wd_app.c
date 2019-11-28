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

#define UNUSED(x) (void)(x)

#define SEM_NAME_IS_WATCHED "/is_watched"
#define SEM_NAME_IS_WD_READY "/is_wd_ready"
#define SEM_NAME_IS_WDT_READY "/is_wdt_ready"

sem_t *is_watched, *is_wd_ready, *is_wdt_ready;
pid_t uapp_pid = 0;

int main (int argc, char *argv[])
{
    scheduler_t *sched = NULL;
    struct sigaction sa1;

    UNUSED(argc);

    printf("watchdog started\n");

    sa1.sa_handler = &ResetCounter;
    sigemptyset(&sa1.sa_mask);
    sa1.sa_flags = 0;
    sigaction(SIGUSR1, &sa1, NULL);

    is_wd_ready = sem_open(SEM_NAME_IS_WD_READY, O_CREAT);
    is_wdt_ready = sem_open(SEM_NAME_IS_WDT_READY, O_CREAT);
    is_watched = sem_open(SEM_NAME_IS_WATCHED, O_CREAT);

    uapp_pid = getppid();
    sched = InitScheduler(Ping, ReviveUAppIfDead, &uapp_pid, argv + 1);

    sem_post(is_wd_ready);
    printf("sem_post(is_wdt_ready)\n");
    printf("before sem_wait(is_wd_ready)\n");
    sem_wait(is_wdt_ready);
    printf("after sem_wait(is_wd_ready)\n");
    sem_post(is_watched);
    printf("sem_post(is_watched)\n");

    TSRun(sched);

    return 0;
}

int CreateUApp(void *uargv)
{
    // printf("%s\n", (char *)uargv);
    uapp_pid = fork();

    if (uapp_pid == 0) /* child - revived user process */
    {
        /*execv(*(char **)uargv, (char **)(uargv) + 1);*/
        execv("./user_app.out", NULL);
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
    printf("WD: thread counter = %d\n", interval_counter);

    if (interval_counter > atoi(getenv("WD_MAXINTERVALS")))
    {
        printf("uapp is dead\n");
        /*printf("%s\n", *(char **)uargv);*/
        interval_counter = 0;
        CreateUApp(uargv);
        printf("reviveuapp: before sem_wait(is_wdt_ready)\n");
        sem_wait(is_wdt_ready);
        printf("reviveuapp: after sem_wait(is_wdt_ready)\n");
        sem_post(is_watched);
    }

    return (WD_SUCCESS);
}
    