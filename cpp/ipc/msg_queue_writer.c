#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main()
{

struct msgbuf 
{
    long mtype;
    char mtext[80];
} msg1;

int key;
int msgid;
int type = 1;

key = ftok("msgq", 65);
msgid = msgget(key, 0666 | IPC_CREAT);

msg1.mtype = type;
strcpy(msg1.mtext, "Hello");

printf("writer, pid: %d\n", getpid());

msgsnd(msgid, &msg1, sizeof(msg1.mtext), 0);
msgsnd(msgid, &msg1, sizeof(msg1.mtext), 0);
msgsnd(msgid, &msg1, sizeof(msg1.mtext), 0);
msgsnd(msgid, &msg1, sizeof(msg1.mtext), 0);

return 0;
}