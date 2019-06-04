
#include <string.h>

#include "hal_module.h"
#include "io_module.h"



//---------------- Private --------------------------//

/// Client requested callbacks.
static fpDigInputCallback p_digInputCallbacks[DIG_IN_END];

/// Callback for hal_module generated interrupts.
/// @param which Specific input number.
/// @param value The new value.
static void p_digInterruptHandler(unsigned int which, bool value);



//---------------- Public API Implementation -------------//

//--------------------------------------------------------//
status_t io_init(void)
{
    status_t stat = STATUS_OK;

    memset(p_digInputCallbacks, 0x00, sizeof(p_digInputCallbacks));

    stat = hal_regDigInterrupt(p_digInterruptHandler);

    return stat;
}

//--------------------------------------------------------//
status_t io_regDigInputCallback(digInput_t which, fpDigInputCallback fp)
{
    status_t stat = STATUS_OK;

    if(which < DIG_IN_END)
    {
        p_digInputCallbacks[which] = fp;
    }
    else
    {
        stat = STATUS_ERROR;   
    }

    return stat;
}

//--------------------------------------------------------//
status_t io_setDigOutput(digOutput_t which, bool value)
{
    status_t stat = STATUS_OK;

    if(which < NUM_DIG_PINS)
    {
        hal_writeDig(which, value);
    }
    else
    {
        stat = STATUS_ERROR;   
    }

    return stat;
}

//--------------------------------------------------------//
status_t io_getDigInput(digInput_t which, bool* value)
{
    status_t stat = STATUS_OK;

    if(which < NUM_DIG_PINS)
    {
        stat = hal_readDig(which, value);
    }
    else
    {
        stat = STATUS_ERROR;   
    }

    return stat;
}

//--------------------------------------------------------//
status_t io_getDigOutput(digOutput_t which, bool* value)
{
    status_t stat = STATUS_OK;

    if(which < NUM_DIG_PINS)
    {
        stat = hal_readDig(which, value);
    }
    else
    {
        stat = STATUS_ERROR;   
    }

    return stat;
}



//---------------- Private --------------------------//

//--------------------------------------------------------//
void p_digInterruptHandler(unsigned int which, bool value)
{
    if(which < NUM_DIG_PINS)
    {
        // Fire callback for registered client.
        if(p_digInputCallbacks[which] != NULL)
        {
            digInput_t din = (digInput_t)which; // Don't ever do this!
            p_digInputCallbacks[which](din, value);
        }
    }
    //else error???
}
