#include <stdlib.h>
#include "DError.h"

DEXPORT const char* DGetErrMsg(DError errCode)
{
    const char *errMsg = NULL;

    switch (errCode) {
    case DERR_OK:
        errMsg = "ok";
        break;
    case DERR_INVALID_ARGS:
        errMsg = "invalid arguments";
        break;
    case DERR_INVALID_PATH:
        errMsg = "invalid path";
        break;
    case DERR_EMPTY_FILE:
        errMsg = "empty file";
        break;
    case DERR_NO_MEMORY:
        errMsg = "no memory";
        break;
    case DERR_BAD_CONTENT_ENCODING:
        errMsg = "bad content encoding";
        break;
    case DERR_MAX:
        errMsg = "max error";
        break;
    default:
        errMsg = "unknown error";
        break;
    }

    return errMsg;
}
