/*
 * @author Double
 * @since 2016/08/21
 */

#ifndef D_FILE_H
#define D_FILE_H

#include <stdint.h>
#include "DExport.h"
#include "DError.h"

#ifdef __cplusplus
extern "C" {
#endif

DEXPORT DError DFileRead(const char *path, char **buf, int32_t *size);
DEXPORT DError DFileWrite(const char *path, const char *buf, int32_t size);
DEXPORT void DFileFlush(const char *path);

#ifdef __cplusplus
}
#endif

#endif // D_FILE_H
