#ifndef _UID_H_
#define _UID_H_

/* Rev. 1.4*/ 
/* 15.09.19  18:40 */

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

const ilrd_uid_t bad_uid;

/*complexity of time() and getpid()*/
ilrd_uid_t UIDCreate(void);

int UIDIsSame(ilrd_uid_t uid1, ilrd_uid_t uid2);

int UIDIsBad(ilrd_uid_t uid);

#endif
