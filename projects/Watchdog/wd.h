#ifndef _WD_H_
#define _WD_H_

/* Rev. 1.0 */ 
/* 27.11.19  17:00 */

#include <stdlib.h>

#define WD_PATH "./wd.out"

typedef enum {WD_SUCCESS = 0, WD_FAILURE = 1} wd_status_t;

/* 
Starts Watchdog, which will run until DNR() is called.
In case the program (specified in uargv) did not respond after a period of
time (interval * max_intervals), Watchdog will continue to run and revive program.
Returns WD_SUCCESS if Watchdog has started successfully, or WD_FAILURE in case of error.
WD_PATH specifies the Watchdog executable full path.
*/
wd_status_t MMI(const char *uargv[], size_t interval, size_t max_intervals);

/* Stops Watchdog */
void DNR(void);

#endif /* _WD_H_ */