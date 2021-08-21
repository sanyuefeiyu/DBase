#include <windows.h>
#include <mmsystem.h>
#include "DTime.h"

#pragma comment(lib,"winmm.lib")

DEXPORT int64_t DTimeGetTickMs()
{
    return timeGetTime();
}
