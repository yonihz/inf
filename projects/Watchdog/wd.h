#ifndef _WATCHDOG_H_
#define _WATCHDOG_H_

/* Rev. 0.3 (missing DNR) */ 
/* 26.11.19  15:00 */

#include <stdlib.h>

#define WD_PATH ./

typedef enum {SUCCESS = 0, FAIL = 1} status_t;

/* 
Starts Watchdog, which will run until DNR() is called.
In case the program (specified in uargv) did not respond after a period of
time (interval * max_intervals), Watchdog will continue to run and revive program.
Returns SUCCESS if Watchdog has started successfully, or FAILURE in case of error.
In order to run, wd.out must exist in WD_PATH.
*/
status_t MMI(const char *uargv[], const size_t interval, size_t max_intervals);

#endif /* _WATCHDOG_H_ */