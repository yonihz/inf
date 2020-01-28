#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{

struct msgbuf 
{
    long mtype;
    char mtext[80];
} msg_toread;

int key;
int msgid;
int type = 1;

key = ftok("msgq", 65);
msgid = msgget(key, 0666 | IPC_CREAT);

msgrcv(msgid, &msg_toread, sizeof(msg_toread.mtext), type, 0);
printf("reader, pid: %d, msg: %s\n", getpid(), msg_toread.mtext);
// msgctl(msgid, IPC_RMID, NULL);
return 0;
}