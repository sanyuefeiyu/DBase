#include <cstdio>
#include <cstdarg>
#include <windows.h>
#include "DFile.h"
#include "DLogCommon.h"
#include "DLog.h"

static char gLogPath[LOG_PATH_LENGTH + 1] = { 0 };

void DLogOutput(DLogMode logMode, DLogLevel level, const char *tag, const char *buf)
{
    char outputBuf[LOG_BUF_SIZE + 256];

    // get date time
    SYSTEMTIME  lt;
    GetLocalTime(&lt);

    // date time pid tid level tag msg
    int size = _snprintf(outputBuf, LOG_BUF_SIZE + 256, "%04d-%02d-%02d %02d:%02d:%02d:%03d [%d|%d] %s|%s %s\r\n",
        lt.wYear, lt.wMonth, lt.wDay, lt.wHour, lt.wMinute, lt.wSecond, lt.wMilliseconds,
        GetCurrentProcessId(), GetCurrentThreadId(),
        gLogLevelDes[level], tag,
        buf);

    if (size <= 0) {
        return;
    }

    // write log to console
    if (logMode & DLOG_CONSOLE) {
        OutputDebugStringA(outputBuf);
    }

    // write log to file
    if (logMode & DLOG_FILE) {
        FILE *fp = fopen(gLogPath, "ab+");
        if (fp == NULL) {
            return;
        }
        fwrite(outputBuf, size, 1, fp);
        fclose(fp);
    }
}

DEXPORT void DLogSetOutputPath(const char *path)
{
    strncpy(gLogPath, path, LOG_PATH_LENGTH);
}
