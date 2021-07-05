
#include <stdarg.h>
#include <string.h>

#include "common_module.h"
#include "common_private.h"
#include "hal_module.h"


//---------------- Private Declarations ------------------//

static int p_log_level = 0;

static char p_log_buff[100];

//---------------- Public API Implementation -------------//

//--------------------------------------------------------//
void common_SetLogLevel(int level)
{
    p_log_level = level;
}

//--------------------------------------------------------//
void common_Log(int level, const char* format, ...)
{
    if(p_log_level > 0 && level <= p_log_level)
    {
        va_list args;
        va_start(args, format);
        vsnprintf(p_log_buff, sizeof(p_log_buff), format, args);
        hal_Log(p_log_buff);
    }
}

//---------------- Private Implementation ----------------//

