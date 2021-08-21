#include "DCommon.h"
#include "DLogInternal.h"
#include "DBase.h"

DEXPORT void DBaseInit(DLogLevel logLevel, DLogMode logMode, const char *logPath)
{
    DLogSetOutputPath(logPath);
    DLogSetOutputControl(logLevel, logMode);

    DLogI(TAG, "version: %d.%d.%d, build time: %s %s", VER_MAJOR, VER_MINOR, VER_FEATURE, __DATE__, __TIME__);
}
