
#include <stdarg.h>
#include <string.h>

#include "common_module.h"
#include "common_private.h"
#include "hal_module.h"


//---------------- Private --------------------------//

static int s_logLevel = 0;

static char s_logBuff[100];

//---------------- Public API Implementation -------------//

//--------------------------------------------------------//
void common_setLogLevel(int level)
{
    s_logLevel = level;
}

//--------------------------------------------------------//
void common_log(int level, const char* format, ...)
{
    if(s_logLevel > 0 && level <= s_logLevel)
    {
        va_list args;
        va_start(args, format);
        vsnprintf(s_logBuff, sizeof(s_logBuff), format, args);
        hal_log(s_logBuff);
    }
}

//---------------- Private --------------------------//

