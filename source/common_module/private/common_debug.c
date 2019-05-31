
#include <stdarg.h>
#include <string.h>

#include "common_module.h"
#include "common_private.h"


//---------------- Private --------------------------//

int s_logLevel;


//---------------- Public API Implementation -------------//

void common_setLogLevel(int level)
{
    s_logLevel = level;
}

void common_debugLog(int level, const char* format, ...)
{
    static char s_buff[100];

    if(s_logLevel > 0 && level <= s_logLevel)
    {
        va_list args;
        va_start(args, format);

        //to get rid of the warning when -Wformat-security is enabled.
        vsnprintf(s_buff, sizeof(s_buff), format, args);
        printf("%s", s_buff);
        //puts(s_buff);

        // if(format[strlen(format) - 1] != '\n')
        // {
        //     printf("\n");
        // }
    }
}

//---------------- Private --------------------------//

