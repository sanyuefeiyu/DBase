#include <windows.h>
#include "DCommon.h"
#include "DMisc.h"
#include "DLog.h"
#include "DLoad.h"

DEXPORT void *DLoadOpen(const char *path)
{
    if (path == nullptr) {
        return nullptr;
    }

    HMODULE hDllLib = LoadLibrary(path);
    DLogD(TAG, "DLoadOpen %s and result is %p", path, hDllLib);
    if (hDllLib == nullptr) {
        DMiscPrintError(DLOG_W);
    }

    return hDllLib;
}

DEXPORT void *DLoadGetSymbol(const void *handle, const char *symbol)
{
    if (handle == nullptr || symbol == nullptr) {
        return nullptr;
    }

    FARPROC proc = GetProcAddress((HMODULE)handle, symbol);
    DLogD(TAG, "DLoadGetSymbol %p, %s and result is %p", handle, symbol, proc);
    if (proc == nullptr) {
        DMiscPrintError(DLOG_W);
    }

    return proc;
}

DEXPORT void DLoadClose(const void *handle)
{
    if (handle == nullptr) {
        return;
    }

    DLogD(TAG, "DLoadClose %p", handle);
    FreeLibrary((HMODULE)handle);
}
