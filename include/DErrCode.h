/*
 * @author Double
 * @since 2018/09/24
 */

#ifndef D_ERR_CODE_H
#define D_ERR_CODE_H

typedef enum
{
    DERR_OK = 0, 
    DERR_OUT_OF_MEMORY,
    DERR_BAD_CONTENT_ENCODING,
    DERR_LAST //never use!
} DErrCode;

#endif /* D_ERR_CODE_H */
