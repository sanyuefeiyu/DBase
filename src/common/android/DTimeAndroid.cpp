#include <time.h>
#include "DExport.h"
#include "DTime.h"

DEXPORT long long DTimeGetTick()
{
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv, &tz);

    long long tick = tv.tv_sec;
    tick = tick * 1000;
    tick += (tv.tv_usec / 1000);

    return tick;
}
