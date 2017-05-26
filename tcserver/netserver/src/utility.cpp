#include "utility.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void MUGetLocalTime(LogTime * pLogTime)
{
    if (pLogTime == mpNULL) return;

    struct timeval tv;
    struct tm localTime;

    memset(&tv, 0x00, sizeof(tv));
    memset(&localTime, 0x00, sizeof(localTime));

    gettimeofday(&tv, mpNULL);
    localtime_r(&tv.tv_sec, &localTime);

    memcpy(&(pLogTime->logSec), &localTime, sizeof(localTime));
    pLogTime->logMSec = tv.tv_usec;
}

// hh:mm:ss.xxx [LEV]%s %d format
mpVOID MP_Log(const mpCHAR * pszLevel, const mpCHAR * pszFile, mpINT iLine, const mpCHAR * format, ...)
{
    va_list args;

    printf("[%s]%s %d ", pszLevel, pszFile, iLine);

    va_start(args, format);
    vprintf(format, args);
    printf("\n");
    va_end(args);

    fflush(stdout);
}
