
#include <string.h>

#include "hal_module.h"
#include "io_module.h"




//---------------- Private --------------------------//

extern status_t io_initDig(void);

//---------------- Public API Implementation -------------//

//--------------------------------------------------------//
status_t io_init(void)
{
    status_t stat = STATUS_OK;

    stat = io_initDig();

    return stat;
}


//--------------------------------------------------------//
status_t io_destroy(void)
{
    status_t stat = STATUS_OK;
  
    return stat;
}
