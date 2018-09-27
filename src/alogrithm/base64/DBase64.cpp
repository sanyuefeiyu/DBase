#include <stdlib.h>
#include <string.h>
#include "DBase64.h"
#include "DStd.h"

//Base64 Encoding/Decoding Table
static const char base64[]= "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
//The Base 64 encoding with an URL and filename safe alphabet, RFC 4648 section 5
static const char base64url[]= "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";

#define D_MASK_SCHAR  0x7F
#define D_MASK_UCHAR  0xFF

//unsigned long to unsigned char
static unsigned char DUL2UC(unsigned long ulNum)
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

DEXPORT DErrCode DBase64Decode(unsigned char **dst, size_t *dstLen, const char *src)
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

static DErrCode Base64Encode(const char *table64, const char *src, size_t srcLen, char **dst, size_t *dstLen)
{
    *dst = NULL;
    *dstLen = 0;

    const char *indata = src;
    if (!srcLen)
        srcLen = strlen(indata);

    char *output;
    char *base64data;
    base64data = output = (char*)malloc(srcLen * 4 / 3 + 4);
    if (!output)
        return  DERR_OUT_OF_MEMORY;

    /*
    * The base64 data needs to be created using the network encoding
    * not the host encoding.  And we can't change the actual input
    * so we copy it to a buffer, translate it, and use that instead.
    */
    DErrCode result;
    // char *convbuf = NULL;
    // //result = Curl_convert_clone(data, indata, srcLen, &convbuf);
    // if (result)
    // {
    //     free(output);
    //     return result;
    // }

    // if (convbuf)
    //     indata = (char*)convbuf;

    unsigned char ibuf[3];
    unsigned char obuf[4];
    int inputparts;
    while (srcLen > 0)
    {
        for (int i = inputparts = 0; i < 3; i++)
        {
            if (srcLen > 0)
            {
                inputparts++;
                ibuf[i] = (unsigned char) *indata;
                indata++;
                srcLen--;
            }
            else
            {
                ibuf[i] = 0;
            }
        }

        obuf[0] = (unsigned char) ((ibuf[0] & 0xFC) >> 2);
        obuf[1] = (unsigned char) (((ibuf[0] & 0x03) << 4) | ((ibuf[1] & 0xF0) >> 4));
        obuf[2] = (unsigned char) (((ibuf[1] & 0x0F) << 2) | ((ibuf[2] & 0xC0) >> 6));
        obuf[3] = (unsigned char) (ibuf[2] & 0x3F);

        switch (inputparts)
        {
        case 1: //only one byte read
            snprintf(output, 5, "%c%c==", table64[obuf[0]], table64[obuf[1]]);
            break;

        case 2: //two bytes read
            snprintf(output, 5, "%c%c%c=", table64[obuf[0]], table64[obuf[1]], table64[obuf[2]]);
            break;

        default:
            snprintf(output, 5, "%c%c%c%c", table64[obuf[0]], table64[obuf[1]], table64[obuf[2]], table64[obuf[3]]);
            break;
        }
        output += 4;
    }

    //Zero terminate
    *output = '\0';

    //Return the pointer to the new data (allocated memory)
    *dst = base64data;

    // free(convbuf);

    //Return the length of the new data
    *dstLen = strlen(base64data);

    return DERR_OK;
}

DEXPORT DErrCode DBase64Encode(char **dst, size_t *dstLen, const char *src, size_t srcLen)
{
    return Base64Encode(base64, src, srcLen, dst, dstLen);
}

DEXPORT DErrCode DBase64UrlEncode(char **dst, size_t *dstLen, const char *src, size_t srcLen)
{
    return Base64Encode(base64url, src, srcLen, dst, dstLen);
}
