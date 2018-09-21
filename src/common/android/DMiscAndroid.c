#include <string.h>
#include <errno.h>
#include "DExport.h"
#include "DCommon.h"
#include "DLog.h"
#include "DMisc.h"

DEXPORT void DMiscPrintError(DLogLevel level)
{
    int errorCode = errno;
    DLog(level, TAG, "lastError is %d, %s", errorCode, strerror(errorCode));
}
