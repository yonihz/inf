#include <stdio.h>          /* printf */
#include <stdlib.h>         /* setenv, getenv */

#include <fcntl.h>          /* O_* constants */
#include <semaphore.h>      /* sem_* functions */ 

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
    struct sigaction sa1, sa2;

    UNUSED(argc);

    printf("watchdog started\n");

    sa1.sa_handler = &ResetCounter;
    sigemptyset(&sa1.sa_mask);
    sa1.sa_flags = 0;
    sigaction(SIGUSR1, &sa1, NULL);

    sa2.sa_handler = &DNRHandler;
    sigemptyset(&sa2.sa_mask);
    sa2.sa_flags = 0;
    sigaction(SIGUSR2, &sa2, NULL);

    is_wd_ready = sem_open(SEM_NAME_IS_WD_READY, O_CREAT);
    is_wdt_ready = sem_open(SEM_NAME_IS_WDT_READY, O_CREAT);
    is_watched = sem_open(SEM_NAME_IS_WATCHED, O_CREAT);

    uapp_pid = getppid();

    /* argv[0]: user program path, argv[1]: user program's argv */ 
    sched = InitScheduler(Ping, ReviveUAppIfDead, &uapp_pid, argv);

    // printf("WD: sem_post(is_wdt_ready)\n");
    sem_post(is_wd_ready);
    // printf("WD: before sem_wait(is_wd_ready)\n");
    sem_wait(is_wdt_ready);
    // printf("WD: after sem_wait(is_wd_ready)\n");
    // printf("WD: sem_post(is_watched)\n");
    sem_post(is_watched);

    TSRun(sched);
    TSDestroy(sched);
    // printf("wd sched finished\n");
    sem_post(is_wd_ready);

    // printf("wd end\n");
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
    // printf("WD: thread counter = %d\n", interval_counter);

    if (0 != is_dnr)
    {
        return (REMOVE_TASK);
    }

    if (interval_counter >= atoi(getenv("WD_MAXINTERVALS")))
    {
        interval_counter = 0;
        printf("revive uapp: %s\n", *(char **)uargv);
        CreateUApp(uargv);
        // printf("revive uapp: before sem_wait(is_wdt_ready)\n");
        sem_wait(is_wdt_ready);
        // printf("revive uapp: after sem_wait(is_wdt_ready)\n");
        // printf("revive uapp: sem_post(is_watched)\n");
        sem_post(is_watched);
    }

    return (WD_SUCCESS);
}
    