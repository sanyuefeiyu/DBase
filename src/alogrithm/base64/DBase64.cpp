#include <stdlib.h>
#include <string.h>
#include "DBase64.h"

//Base64 Encoding/Decoding Table
static const char base64[]= "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

#define D_MASK_SCHAR  0x7F
#define D_MASK_UCHAR  0xFF

//unsigned long to unsigned char
unsigned char DUL2UC(unsigned long ulNum)
{
    return (unsigned char)(ulNum & (unsigned long) D_MASK_UCHAR);
}

static size_t DecodeQuantum(unsigned char *dst, const char *src)
{
    size_t padding = 0;
    unsigned long x = 0;
    unsigned long i;
    const char *s;

    for (i = 0, s = src; i < 4; i++, s++)
    {
        if (*s == '=')
        {
            x = (x << 6);
            padding++;
        }
        else
        {
            unsigned long v = 0;
            const char *p = base64;

            while (*p && (*p != *s))
            {
                v++;
                p++;
            }

            if(*p == *s)
                x = (x << 6) + v;
            else
                return 0;
        }
    }

    if (padding < 1)
        dst[2] = DUL2UC(x & 0xFFUL);

    x >>= 8;
    if (padding < 2)
        dst[1] = DUL2UC(x & 0xFFUL);

    x >>= 8;
    dst[0] = DUL2UC(x & 0xFFUL);

    return 3 - padding;
}

DErrCode DBase64Decode(unsigned char **dst, size_t *dstLen, const char *src)
{
    *dst = NULL;
    *dstLen = 0;

    //Check the length of the input string is valid
    size_t srcLen = strlen(src);
    if (!srcLen || srcLen % 4)
        return DERR_BAD_CONTENT_ENCODING;

    //Find the position of any = padding characters
    size_t length = 0;
    while ((src[length] != '=') && src[length])
        length++;

    //A maximum of two = padding characters is allowed
    size_t padding = 0;
    if (src[length] == '=')
    {
        padding++;
        if (src[length + 1] == '=')
            padding++;
    }

    //Check the = padding characters weren't part way through the input
    if (length + padding != srcLen)
        return DERR_BAD_CONTENT_ENCODING;

    //Calculate the number of quantums
    size_t numQuantums = srcLen / 4;

    //Calculate the size of the decoded string
    size_t rawLen = (numQuantums * 3) - padding;

    //Allocate our buffer including room for a zero terminator
    unsigned char *newStr = (unsigned char*)malloc(rawLen + 1);
    if (!newStr)
        return DERR_OUT_OF_MEMORY;

    unsigned char *pos = newStr;

    //Decode the quantums
    for(size_t i = 0; i < numQuantums; i++)
    {
        size_t result = DecodeQuantum(pos, src);
        if(!result)
        {
            free(newStr);
            return DERR_BAD_CONTENT_ENCODING;
        }

        pos += result;
        src += 4;
    }

    //Zero terminate
    *pos = '\0';

    //Return the decoded data
    *dst = newStr;
    *dstLen = rawLen;

    return DERR_OK;
}
