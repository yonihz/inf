#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

/* version 0.7 */
/* date 19.09.19 */
/* time 15:30 */

#include <stddef.h> /* size_t */
#include "uid.h"

typedef int (*op_func_t)(void* param);
typedef struct scheduler scheduler_t;

scheduler_t* TSCreate();
void TSDestroy(scheduler_t* scheduler);
int TSIsEmpty(const scheduler_t* scheduler);
size_t TSSize(const scheduler_t* scheduler);

/* if the op_func_t return 1 - loop is stopped and run() returns 2 */
ilrd_uid_t TSAdd(
	scheduler_t* scheduler,
	size_t interval, 
	op_func_t operation,
	void* param);

/* returns 0 if successful */
int TSRemove(scheduler_t* scheduler, ilrd_uid_t task_uid);
void TSClear(scheduler_t* scheduler);

/* return 0 if no more tasks to run */
/* return 1 if a stop task was executd */
/* return 2 in case of error such as op_func returning 1 */
int TSRun(scheduler_t* scheduler);
void TSStop(scheduler_t* scheduler);

#endif
