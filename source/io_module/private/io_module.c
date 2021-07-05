
#include <string.h>

#include "hal_module.h"
#include "io_module.h"




//---------------- Private Declarations ------------------//

extern status_t io_InitDig(void);

//---------------- Public API Implementation -------------//

//--------------------------------------------------------//
status_t io_Init(void)
{
    status_t stat = STATUS_OK;

    stat = io_InitDig();

    return stat;
}


//--------------------------------------------------------//
status_t io_Destroy(void)
{
    status_t stat = STATUS_OK;
  
    return stat;
}

//---------------- Private Implementation ----------------//
