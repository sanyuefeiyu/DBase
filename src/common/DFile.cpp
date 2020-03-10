#include <stdlib.h>
#include <stdio.h>
#include "DCommon.h"
#include "DLog.h"
#include "DFile.h"

DEXPORT DError DFileRead(const char *path, char **buf, int *size)
{
    if (path == NULL || buf == NULL || size == NULL) {
        return DERR_INVALID_ARGS;
    }

    FILE *fp = fopen(path, "rb+");
    if (fp == NULL) {
        DLog(DLOG_W, TAG, "open file failed, path is %s", path);
        return DERR_INVALID_PATH;
    }

    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if (fileSize <= 0) {
        fclose(fp);
        return DERR_EMPTY_FILE;
    }

    char *tempBuf = (char*)malloc(fileSize);;
    if (tempBuf == NULL) {
        fclose(fp);
        return DERR_NO_MEMORY;
    }
    size_t readSize = fread(tempBuf, 1, fileSize, fp);
    if (readSize <= 0) {
        free(tempBuf);
        fclose(fp);
        return DERR_EMPTY_FILE;
    }

    *buf = tempBuf;
    *size = readSize;
    fclose(fp);
    return DERR_OK;
}

DEXPORT DError DFileWrite(const char *path, const char *buf, int size)
{
    if (path == NULL || buf == NULL || size <= 0) {
        return DERR_INVALID_ARGS;
    }

    FILE *fp = fopen(path, "ab+");
    if (fp == NULL) {
        DLog(DLOG_W, TAG, "open file failed, path is %s", path);
        return DERR_INVALID_PATH;
    }

    fwrite(buf, size, 1, fp);
    fclose(fp);
    return DERR_OK;
}

DEXPORT void DFileFlush(const char *path)
{
    FILE *fp = fopen(path, "wb+");
    if (fp == NULL) {
        DLog(DLOG_W, TAG, "flush file failed, path is %s", path);
        return;
    }
    fclose(fp);
}
