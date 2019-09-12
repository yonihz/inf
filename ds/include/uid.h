#ifndef _UID_H_
#define _UID_H_

/* Rev. 1.2*/ 
/* 12.09.19  16:41 */

#include <stddef.h> /*size_t*/
#include <time.h> /*time()*/
#include <sys/types.h> /*pid_t, getpid()*/
#include <unistd.h> /*getpid()*/

typedef struct
{
    size_t counter;
    time_t time;
    pid_t pid;
} ilrd_uid_t;

/*complexity of time() and getpid()*/
ilrd_uid_t UIDCreate(void);

int UIDIsSame(ilrd_uid_t uid1, ilrd_uid_t uid2);

int UIDIsBad(ilrd_uid_t uid);

#endif
