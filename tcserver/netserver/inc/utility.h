#ifndef __NET_SERVER_UTILITY_H__
#define __NET_SERVER_UTILITY_H__

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#define mpINT       int
#define mpCHAR      char
#define mpVOID      void
#define mpNULL      NULL

#define MP_MALLOC       malloc
#define MP_FREE         free

#define LEV_ERR                "ERR"
#define LEV_WAR                "WAR"
#define LEV_INF                "INF"
#define LEV_DBG                "DBG"

#define NS_ERR(format, ...)        MP_Log(LEV_ERR, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define NS_WAR(format, ...)        MP_Log(LEV_WAR, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define NS_INF(format, ...)        MP_Log(LEV_INF, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define NS_DBG(format, ...)        MP_Log(LEV_DBG, __FILE__, __LINE__, format, ##__VA_ARGS__)

mpVOID MP_Log(const mpCHAR * pszLevel, const mpCHAR * pszFile, mpINT iLine, const mpCHAR * format, ...);

typedef struct _tagLogTime
{
    struct tm logSec;
    mpINT logMSec;

} LogTime;

#endif

