/* test commands:
$ pkill wd.out
$ pkill user_app.out
$ ps -e | grep user_app.out
$ ps -e | grep wd.out
*/

#include <unistd.h> /* sleep */
#include <stdio.h> /* printf */

#include "wd.h"

#define UNUSED(x) (void)(x)

int main(int argc, const char* argv[])
{
    size_t interval = 2;
    size_t max_intervals = 3;
    time_t time_left = 0;

    UNUSED(argc);

    MMI(argv, interval, max_intervals);

    printf("Critical code started\n");

    time_left =	1000;
    while (time_left)
    {
        time_left = sleep(time_left);
    }

    DNR();
}