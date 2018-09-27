/*
 * @author Double
 * @since 2018/09/24
 */

#ifndef D_BASE64_H
#define D_BASE64_H

#include "DExport.h"
#include "DErrCode.h"

#ifdef __cplusplus
extern "C" {
#endif

DEXPORT DErrCode DBase64Decode(unsigned char **dst, size_t *dstLen, const char *src);
DEXPORT DErrCode DBase64Encode(char **dst, size_t *dstLen, const char *src, size_t srcLen);
DEXPORT DErrCode DBase64UrlEncode(char **dst, size_t *dstLen, const char *src, size_t srcLen);

#ifdef __cplusplus
}
#endif

#endif /* D_BASE64_H */
