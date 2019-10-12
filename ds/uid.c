/****************************************************************
* 																*
* FILE NAME: uid.c												*
* 																*
* PURPOSE: UID functions source file							*
* 																*
* DATE: 12.09.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
****************************************************************/

#include "uid.h"

static size_t counter = 0;
const ilrd_uid_t bad_uid = {0, (time_t)-1, 0};

ilrd_uid_t UIDCreate(void)
{
	ilrd_uid_t new_uid;

	counter++;
	new_uid.counter = counter;
	new_uid.time = time(NULL);
	new_uid.pid = getpid();

	return (new_uid);
}

int UIDIsSame(ilrd_uid_t uid1, ilrd_uid_t uid2)
{
	return (uid1.counter == uid2.counter &&
		uid1.time == uid2.time &&
		uid1.pid == uid2.pid);
}

int UIDIsBad(ilrd_uid_t uid)
{
	return (UIDIsSame(uid, bad_uid));
}	
