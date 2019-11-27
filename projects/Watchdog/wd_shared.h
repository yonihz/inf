#ifndef _WD_SHARED_H_
#define _WD_SHARED_H_

#include "scheduler.h"

sig_atomic_t counter = 0;

scheduler_t *InitScheduler(op_func_t PingFunc, op_func_t ReviveFunc, pid_t pid);

void ResetCounter(int signum);

int Ping(void *pid);

#endif /* _WD_SHARED_H_ */