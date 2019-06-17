
#include <stdarg.h>

#include "common_module.h"
#include "common_private.h"


//---------------- Private --------------------------//


//---------------- Public API Implementation -------------//

//--------------------------------------------------------//
status_t common_init(void)
{
    status_t stat = STATUS_OK;

    common_setLogLevel(0); // default is off

    return stat;
}


//--------------------------------------------------------//
status_t common_destroy(void)
{
    status_t stat = STATUS_OK;
  
    return stat;
}


//---------------- Private --------------------------//



