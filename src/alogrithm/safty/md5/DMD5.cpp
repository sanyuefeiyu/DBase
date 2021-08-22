#include <cstdlib>
#include <cstdio>
extern "C" {
#include "./cifs/MD5.h"
}

#include "DCommon.h"
#include "DMisc.h"
#include "DLog.h"
#include "DMD5.h"

#define MD5_BLOCK   64
#define READ_SIZE   (4*1024)

struct DMD5Ctx
{
    auth_md5Ctx cifs_ctx[1];
};

DEXPORT DMD5Ctx *DMD5InitCtx()
{
    DMD5Ctx *ctx = new DMD5Ctx;
    if (ctx == nullptr) {
        return nullptr;
    }

    auth_md5InitCtx(ctx->cifs_ctx);
    return ctx;
}

DEXPORT void DMD5SumCtx(DMD5Ctx *ctx, const unsigned char *src, const int len)
{
    int consumedSize = 0;

    if (ctx == nullptr || src == nullptr || len <= 0) {
        return;
    }

    while (consumedSize < len) {
        int size = len - consumedSize;
        if (size >= MD5_BLOCK) {
            size = MD5_BLOCK;
        }

        auth_md5SumCtx(ctx->cifs_ctx, src + consumedSize, size);
        consumedSize += size;
    }
}

DEXPORT void DMD5CloseCtx(DMD5Ctx *ctx, unsigned char *dst)
{
    if (ctx == nullptr || dst == nullptr) {
        return;
    }

    auth_md5CloseCtx(ctx->cifs_ctx, dst);
}

DEXPORT void DMD5ReleaseCtx(DMD5Ctx **ctx)
{
    if (ctx == nullptr || *ctx == nullptr) {
        return;
    }

    delete *ctx;
}

DEXPORT void DMD5Sum(unsigned char *dst, const unsigned char *src, const int len)
{
    auth_md5Sum(dst, src, len);
}

DEXPORT void DMD5SumFile(unsigned char *dst, const char *path)
{
    long fileSize = 0;
    long readSize = 0;
    unsigned char src[READ_SIZE];
    DMD5Ctx *ctx = nullptr;

    if (dst == nullptr || path == nullptr) {
        return;
    }

    FILE *fp = nullptr;
    errno_t errorCode = fopen_s(&fp, path, "rb");
    if (errorCode != 0 || fp == nullptr) {
        DLogW(TAG, "open file failed, path: %s, %d", path, errorCode);
        DPrintOsErrorByError(DLOG_W, errorCode);
        return;
    }
    fseek(fp, 0, SEEK_END);
    fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if (fileSize <= 0) {
        DLogW(TAG, "file size is 0, path: s", path);
        fclose(fp);
        return;
    }

    ctx = DMD5InitCtx();
    if (ctx == nullptr) {
        fclose(fp);
        return;
    }

    readSize = fread(src, 1, READ_SIZE, fp);
    while (readSize > 0) {
        DMD5SumCtx(ctx, src, readSize);
        readSize = fread(src, 1, READ_SIZE, fp);
    }

    DMD5CloseCtx(ctx, dst);
    DMD5ReleaseCtx(&ctx);
    fclose(fp);
}
