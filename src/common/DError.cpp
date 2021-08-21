#include "DError.h"

DEXPORT const char *DGetErrMsg(DError errCode)
{
    const char *errMsg = nullptr;

    switch (errCode) {
    case DERR_OK:
        errMsg = "ok";
        break;
    case DERR_OUT_OF_MEMORY:
        errMsg = "out of memory";
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
    case DERR_BAD_ENCODING:
        errMsg = "bad encoding";
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
