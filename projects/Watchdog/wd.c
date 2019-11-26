#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>           /* O_* constants */
#include <sys/stat.h>        /* mode constants */
#include <semaphore.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h> /* kill */

#define SEM1_NAME "/is_watched"

sem_t *is_watched;

int main (int argc, char *argv[])
{
    