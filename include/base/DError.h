/*
 * @author Double
 * @since 2018/09/24
 */

#ifndef D_ERROR_H
#define D_ERROR_H

#include "DExport.h"

typedef enum
{
    DERR_OK = 0,
    DERR_OUT_OF_MEMORY,
    DERR_INVALID_ARGS,
    DERR_INVALID_PATH,
    DERR_EMPTY_FILE,
    DERR_BAD_ENCODING,
    DERR_MAX
} DError;

#ifdef __cplusplus
extern "C" {
#endif

DEXPORT const char *DGetErrMsg(DError error);

#ifdef __cplusplus
}
#endif

#endif // D_ERROR_H
