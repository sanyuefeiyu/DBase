/*
 * @author Double
 * @since 2018/09/27
 */

#ifndef D_STD_H
#define D_STD_H

#include <stdio.h>

#if defined(_WIN32)
    #define snprintf    _snprintf
#elif defined(__ANDROID__)
#else
#endif

#endif /* D_STD_H */
