#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/shm.h>

int main()
{

char *str;
key_t key;
int seg_id;

key = ftok("shm", 25);
seg_id = shmget(key, 1024 ,0666 | IPC_CREAT); 
str = (char*) shmat(seg_id,(void*)0,0);

strcpy(str, "Reading from shared memory!");

printf("writer, pid: %d\n", getpid());

return 0;
}