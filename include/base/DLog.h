/*
 * @author Double
 * @since 2016/04/17
 */

#ifndef D_LOG_H
#define D_LOG_H

#include "DExport.h"

typedef enum
{
    DLOG_D = 0,
    DLOG_I,
    DLOG_W,
    DLOG_E
} DLogLevel;

typedef enum
{
    DLOG_NONE = 0x0,
    DLOG_CONSOLE = 0x1,
    DLOG_FILE = 0x1 << 1,
    DLOG_ALL = (DLOG_CONSOLE | DLOG_FILE )
} DLogMode;

#ifdef __cplusplus
extern "C" {
#endif

DEXPORT void DLog(DLogLevel level, const char *tag, const char *format, ...);

#ifdef __cplusplus
}
#endif

#ifdef WIN32
#define DLogD(tag, format, ...)         DLog(DLOG_D, tag, format, ##__VA_ARGS__)
#define DLogI(tag, format, ...)         DLog(DLOG_I, tag, format, ##__VA_ARGS__)
#define DLogW(tag, format, ...)         DLog(DLOG_W, tag, format, ##__VA_ARGS__)
#define DLogE(tag, format, ...)         DLog(DLOG_E, tag, format, ##__VA_ARGS__)
#else
#define DLogD(tag, format, arg ...)     DLog(DLOG_D, tag, format, ##arg)
#define DLogI(tag, format, arg ...)     DLog(DLOG_I, tag, format, ##arg)
#define DLogW(tag, format, arg ...)     DLog(DLOG_W, tag, format, ##arg)
#define DLogE(tag, format, arg ...)     DLog(DLOG_E, tag, format, ##arg)
#endif

#endif // D_LOG_H
