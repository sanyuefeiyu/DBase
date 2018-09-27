/*
 * @author Double
 * @since 2018/09/24
 */

#ifndef D_ERR_CODE_H
#define D_ERR_CODE_H

#include "DExport.h"

typedef enum
{
    DERR_OK = 0,
    DERR_OUT_OF_MEMORY,
    DERR_BAD_CONTENT_ENCODING,
    DERR_LAST
} DErrCode;

#ifdef __cplusplus
extern "C" {
#endif

DEXPORT const char* DGetErrMsg(DErrCode errCode);

#ifdef __cplusplus
}
#endif

#endif /* D_ERR_CODE_H */
