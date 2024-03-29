/*
 * @author Double
 * @since 2017/05/13
 */

#ifndef D_LOAD_H
#define D_LOAD_H

#include "DExport.h"

#ifdef __cplusplus
extern "C" {
#endif

DEXPORT void *DLoadOpen(const char *path);
DEXPORT void *DLoadGetSymbol(const void *handle, const char *symbol);
DEXPORT void DLoadClose(const void *handle);

#ifdef __cplusplus
}
#endif

#endif // D_LOAD_H
