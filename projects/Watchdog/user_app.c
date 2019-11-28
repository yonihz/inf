#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <signal.h>

#include "wd.h"
#include "wd_shared.h"

#define UNUSED(x) (void)(x)

#define SEM_NAME_IS_WATCHED "/is_watched"
#define SEM_NAME_IS_WD_READY "/is_wd_ready"
#define SEM_NAME_IS_WDT_READY "/is_wdt_ready"

int main(int argc, const char* argv[])
{
    struct sigaction sa1;
    size_t interval = 3;
    size_t max_intervals = 3;

    UNUSED(argc);

    sa1.sa_handler = &ResetCounter;
    sigemptyset(&sa1.sa_mask);
    sa1.sa_flags = 0;
    sigaction(SIGUSR1, &sa1, NULL);

    sem_unlink(SEM_NAME_IS_WATCHED);
    sem_unlink(SEM_NAME_IS_WD_READY);
    sem_unlink(SEM_NAME_IS_WDT_READY);

    MMI(argv, interval, max_intervals);
    sleep(10000);
}