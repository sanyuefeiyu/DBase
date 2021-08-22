#include <cstdio>
#include <cstdarg>
#include <ctime>
#include "DLogCommon.h"
#include "DLogInternal.h"
#include "DLog.h"

extern void DLogOutputByOs(DLogMode logMode, DLogLevel level, const char *tag, const char *buf);

static DLogLevel gLogOutputlevel = DLOG_D;
static DLogMode gLogMode = DLOG_CONSOLE;

void DLogSetOutputControl(DLogLevel logLevel, DLogMode logMode)
{
    if (logLevel >= DLOG_D && logLevel <= DLOG_E) {
        gLogOutputlevel = logLevel;
    }

    if (logMode >= DLOG_NONE && logMode <= DLOG_ALL) {
        gLogMode = logMode;
    }
}

DEXPORT void DLog(DLogLevel level, const char *tag, const char *format, ...)
{
    if (level < DLOG_D || level > DLOG_E || level < gLogOutputlevel) {
        return;
    }

    if (!(gLogMode & DLOG_ALL)) {
        return;
    }

    char buf[LOG_BUF_SIZE];
    va_list ap;
    va_start(ap, format);
    int size = vsnprintf_s(buf, LOG_BUF_SIZE, format, ap);
    va_end(ap);

    if (size <= 0) {
        return;
    }

    DLogOutputByOs(gLogMode, level, tag, buf);
}
