/*
 * @author Double
 * @since 2018/09/24
 */

#ifndef D_BASE64_H
#define D_BASE64_H

#include "DExport.h"
#include "DError.h"

#ifdef __cplusplus
extern "C" {
#endif

DEXPORT DError DBase64Decode(unsigned char **dst, size_t *dstLen, const char *src);
DEXPORT DError DBase64Encode(char **dst, size_t *dstLen, const char *src, size_t srcLen);
DEXPORT DError DBase64UrlEncode(char **dst, size_t *dstLen, const char *src, size_t srcLen);

#ifdef __cplusplus
}
#endif

#endif /* D_BASE64_H */
