
#include <stdarg.h>

#include "common_module.h"
#include "common_private.h"


//---------------- Private Declarations ------------------//


//---------------- Public API Implementation -------------//

//--------------------------------------------------------//
status_t common_Init(void)
{
    status_t stat = STATUS_OK;

    common_SetLogLevel(0); // default is off

    return stat;
}


//--------------------------------------------------------//
status_t common_Destroy(void)
{
    status_t stat = STATUS_OK;
  
    return stat;
}


//---------------- Private Implementation ----------------//

