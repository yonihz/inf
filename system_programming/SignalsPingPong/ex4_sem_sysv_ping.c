/* int semctl (int semid, int semnum, int cmd, ...);
IPC_STAT - for getting the data from kernel data structures for the semaphore set into the struct semid_ds pointed by buf described below
IPC_SET - for setting some of the fields in the struct semid_ds for the semaphore set
GETALL - for getting values of all semaphores of the set in the array described below
SETALL - for setting initial values of all semaphores in the set
SETVAL - for setting an initial value for a semaphore
IPC_RMID for removing the semaphore set
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/ipc.h>

#define UNUSED(x) (void)(x)

#define SEM_KEY "/tmp/tmp_sem"
#define SETVAL 1

int main()
{
    key_t sem1_key = 0;
    int sem1 = 0;

    union semun  
    {
        int val;
        struct semid_ds *buf;
        unsigned short array [1];
    } sem_attr;

    sem1_key = ftok(SEM_KEY, 'a');
    sem1 = setget(sem1_key, 1, 0660 | IPC_CREAT);
    sem_attr.val = 1;
    semctl(sem1, 0, SETVAL, sem_attr);

    
    if (SEM_FAILED == sem1 || SEM_FAILED == sem2)
    {
        return (0);
    }

    while (1)
    {
        sem_wait(sem1);
        sleep(1);
        printf("Ping\n");
        sem_post(sem2);
    }

    return (0);                                                                                                                                                        
}