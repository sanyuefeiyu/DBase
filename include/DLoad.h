/*
 * @author Double
 * @since 2017/05/13
 */

#ifndef D_LOAD_H
#define D_LOAD_H

#ifdef __cplusplus
extern "C" {
#endif

void* DLoadOpen(const char *path);
void* DLoadGetSymbol(const void *hdl, const char *symbol);
void DLoadClose(const void *hdl);

#ifdef __cplusplus
}
#endif

#endif /* D_LOAD_H */
