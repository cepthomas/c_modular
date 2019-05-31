
#include <stdarg.h>

#include "common_module.h"
#include "common_private.h"


//---------------- Private --------------------------//

static uint64_t s_uSec;



//---------------- Public API Implementation -------------//


status_t common_init(void)
{
    status_t stat = STATUS_OK;

    s_uSec = 0;
    common_setLogLevel(0); // off

    return stat;
}


uint64_t common_getUsec(void)
{
    return s_uSec;
}

//---------------- Private --------------------------//



