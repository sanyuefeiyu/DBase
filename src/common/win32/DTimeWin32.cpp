#include "windows.h"
#include "mmsystem.h"
#include "DTime.h"

#pragma comment(lib,"winmm.lib")

DEXPORT long long DTimeGetTick()
{
    return timeGetTime();
}
