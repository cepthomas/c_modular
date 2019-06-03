
#include <stdarg.h>
#include <string.h>

#include "common_module.h"
#include "common_private.h"
#include "hal_module.h"


//---------------- Private --------------------------//

static int p_logLevel = 0;

static char p_logBuff[100];

//---------------- Public API Implementation -------------//

//--------------------------------------------------------//
void common_setLogLevel(int level)
{
    p_logLevel = level;
}

//--------------------------------------------------------//
void common_log(int level, const char* format, ...)
{
    if(p_logLevel > 0 && level <= p_logLevel)
    {
        va_list args;
        va_start(args, format);
        vsnprintf(p_logBuff, sizeof(p_logBuff), format, args);
        hal_log(p_logBuff);
    }
}

//---------------- Private --------------------------//

