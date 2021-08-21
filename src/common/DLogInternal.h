/*
 * @author Double
 * @since 2021/08/22
 */

#ifndef D_LOG_INTERNAL_H
#define D_LOG_INTERNAL_H

#include "DLog.h"

#ifdef __cplusplus
extern "C" {
#endif

void DLogSetOutputControl(DLogLevel logLevel, DLogMode logMode);
void DLogSetOutputPath(const char *path);

#ifdef __cplusplus
}
#endif

#endif // D_LOG_INTERNAL_H
