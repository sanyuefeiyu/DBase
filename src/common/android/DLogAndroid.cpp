#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <time.h>
#include <android/log.h>
#include "DExport.h"
#include "DLogCommon.h"
#include "DLog.h"
#include "DFile.h"

static char gLogPath[LOG_PATH_LENGTH+1] = {0};

void DLogOutput(DLogMode logMode, DLogLevel level, const char *tag, const char *buf)
{
    // write log to ddms
    if (logMode & DLOG_CONSOLE) {
        __android_log_print(level + 3, tag, "%s", buf);
    }

    if (logMode & DLOG_FILE) {
        struct timeval tv;
        struct timezone tz;
        gettimeofday(&tv, &tz);
        time_t currTime = time(NULL);
        tm tm2 = *localtime(&currTime);

        // write log to file
        char outputBuf[LOG_BUF_SIZE+256];
        int size = snprintf(outputBuf, LOG_BUF_SIZE+256, "%04d-%02d-%02d %02d:%02d:%02d:%03ld [%d|%d] %s|%s %s\r\n",
                            tm2.tm_year+1900, tm2.tm_mon+1, tm2.tm_mday, tm2.tm_hour, tm2.tm_min, tm2.tm_sec, tv.tv_usec/1000,
                            getpid(), gettid(),
                            gLogLevelDes[level], tag, buf);
        if (size <= 0) {
            return;
        }

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
