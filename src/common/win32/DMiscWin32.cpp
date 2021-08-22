#include <windows.h>
#include "DCommon.h"
#include "DLog.h"
#include "DMisc.h"

static LPSTR ConvertErrorCodeToString(DWORD errorCode)
{
    HLOCAL LocalAddress = NULL;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM,
        NULL, errorCode, 0, (PTSTR)&LocalAddress, 0, NULL);
    return (LPSTR)LocalAddress;
}

DEXPORT void DPrintOsError(DLogLevel level)
{
    DWORD errorCode = GetLastError();
    DLog(level, TAG, "lastError is %d, %s", errorCode, ConvertErrorCodeToString(errorCode));
}

DEXPORT void DPrintOsErrorByError(DLogLevel level, errno_t errorCode)
{
    DLog(level, TAG, "error is %d, %s", errorCode, ConvertErrorCodeToString(errorCode));
}
