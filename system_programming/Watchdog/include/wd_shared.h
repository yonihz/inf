#ifndef _WD_SHARED_H_
#define _WD_SHARED_H_

#include <signal.h>         /* sigaction */
#include <fcntl.h>          /* O_* constants */
#include <semaphore.h>      /* sem_* functions */ 

#include "scheduler.h"

#define SEM_NAME_IS_WATCHED "/is_watched"
#define SEM_NAME_IS_WD_READY "/is_wd_ready"
#define SEM_NAME_IS_WDT_READY "/is_wdt_ready"

typedef enum {CONT_SCHED = 0, STOP_SCHED = 2} sched_status_t;
typedef struct sigaction sigaction_t;
typedef void(*sa_handler_t)(int signum);

extern sig_atomic_t interval_counter;
extern sig_atomic_t is_dnr;

extern sem_t *is_watched;
extern sem_t *is_wd_ready;
extern sem_t *is_wdt_ready;

scheduler_t *InitScheduler(op_func_t PingFunc, op_func_t ReviveFunc, pid_t *pid_ptr, void *uargv);

void ResetCounter(int signum);

void DNRHandler(int signum);

int Ping(void *pid);

void InitSigHandler(int signum, sa_handler_t handler, sigaction_t *sa);

void ResetSigHandler(int signum, sigaction_t *sa);

void InitSem(void);

#endif /* _WD_SHARED_H_ */