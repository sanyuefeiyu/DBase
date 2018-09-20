#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include "DExport.h"
#include "DLog.h"
#include "DLogCommon.h"

void DLogOutput(DLogMode logMode, DLogLevel level, const char *tag, const char *buf);

static DLogLevel gLogOutputlevel = DLOG_D;
static DLogMode gLogMode = DLOG_CONSOLE;

DEXPORT void DLogSetOutputControl(DLogLevel logLevel, DLogMode logMode)
{
    if (logLevel >= DLOG_D && logLevel <= DLOG_E)
    {
        gLogOutputlevel = logLevel;
    }

    if (logMode >= DLOG_NONE && logMode <= DLOG_ALL)
    {
        gLogMode = logMode;
    }
}

DEXPORT void DLog(DLogLevel level, const char *tag, const char *format, ...)
{
    if (level < DLOG_D || level > DLOG_E || level < gLogOutputlevel)
    {
        return;
    }

    if (!(gLogMode & DLOG_ALL))
    {
        return;
    }

    char buf[LOG_BUF_SIZE];
    va_list ap;
    va_start(ap, format);
    int size = vsnprintf(buf, LOG_BUF_SIZE, format, ap);
    va_end(ap);

    if (size <= 0)
    {
        return;
    }

    DLogOutput(gLogMode, level, tag, buf);
}
