
#include <string.h>

#include "hal_module.h"
#include "io_module.h"




//---------------- Private Declarations ------------------//

extern int io_InitDig(void);

//---------------- Public API Implementation -------------//

//--------------------------------------------------------//
int io_Init(void)
{
    int stat = RS_PASS;

    stat = io_InitDig();

    return stat;
}


//--------------------------------------------------------//
int io_Destroy(void)
{
    int stat = RS_PASS;
  
    return stat;
}

//---------------- Private Implementation ----------------//
