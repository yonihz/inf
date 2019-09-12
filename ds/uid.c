/****************************************************************
* 																*
* FILE NAME: uid.c												*
* 																*
* PURPOSE: UID functions source file							*
*                                                               *
* VERSION: 0.1													*
* 																*
* DATE: 12.09.19												*
* 																*
* Author: Yoni Horovitz											*
* 																*
* Reviewer: N/A													*
* 																*
****************************************************************/

#include "uid.h"

static size_t counter = 0; 

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
	if (uid1.counter == uid2.counter &&
		uid1.time == uid2.time &&
		uid1.pid == uid2.pid)
	{
		return (1);
	}
	return (0);
}

int UIDIsBad(ilrd_uid_t uid)
{
	return (uid.time == -1);
}	
