#include <stdlib.h>
#include "DErrCode.h"

DEXPORT const char* DGetErrMsg(DErrCode errCode)
{
    const char *errMsg = NULL;

    switch (errCode)
    {
    case DERR_OK:
        errMsg = "ok";
        break;
    case DERR_OUT_OF_MEMORY:
        errMsg = "no memory";
        break;
    case DERR_BAD_CONTENT_ENCODING:
        errMsg = "bad content encoding";
        break;
    default:
        errMsg = "unknown error";
        break;
    }

    return errMsg;
}
