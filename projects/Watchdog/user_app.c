#include <stdio.h>

#include "wd.h"

#define UNUSED(x) (void)(x)

int main(int argc, const char* argv[])
{
    UNUSED(argc);
    size_t interval = 3;
    size_t max_intervals = 3;
    MMI(argv, interval, max_intervals);
}