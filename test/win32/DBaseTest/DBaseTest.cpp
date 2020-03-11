// DBaseTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <stdlib.h>
#include <string.h>

#include "DLog.h"
#include "DMD5.h"
#include "DFile.h"
#include "DTime.h"

#define TAG "DBaseTest"

int _tmain(int argc, _TCHAR* argv[])
{
    DLogD(TAG, "begin");
    long long startTick = DTimeGetTick();

    //Test:MD5
    unsigned char md5[256] = { 0 };
    unsigned char src[] = "hello,world";
    DMD5Sum(md5, src, strlen((char*)src));
    DLogD(TAG, "MD5=[%s]", md5);

    DLogD(TAG, "end, const time=%lld", DTimeGetTick() - startTick);

	return 0;
}
