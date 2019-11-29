#ifndef _WD_SHARED_H_
#define _WD_SHARED_H_

#include <signal.h>

#include "scheduler.h"

typedef enum {CONT_SCHED = 0, REMOVE_TASK = 1} sched_status_t;

extern sig_atomic_t interval_counter;
extern sig_atomic_t is_dnr;

scheduler_t *InitScheduler(op_func_t PingFunc, op_func_t ReviveFunc, pid_t *pid_ptr, void *uargv);

void ResetCounter(int signum);

void DNRHandler(int signum);

int Ping(void *pid);

#endif /* _WD_SHARED_H_ */