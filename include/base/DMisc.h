/*
 * @author Double
 * @since 2017/05/13
 */

#ifndef D_MISC_H
#define D_MISC_H

#include "DExport.h"
#include "DLog.h"

#ifdef __cplusplus
extern "C" {
#endif

DEXPORT void DPrintOsError(DLogLevel level);
DEXPORT void DPrintOsErrorByError(DLogLevel level, errno_t errorCode);

#ifdef __cplusplus
}
#endif

#endif // D_MISC_H
