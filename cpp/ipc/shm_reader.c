#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/shm.h>

int main()
{
char *str;
key_t key;
int seg_id;

key = ftok("shm", 25);
seg_id = shmget(key, 1024 ,0666 | IPC_CREAT); 
str = (char*) shmat(seg_id,(void*)0,0);

printf("reader, pid: %d, msg: %s\n", getpid(), str);

return 0;
}