
#include <string.h>

#include "hal_module.h"
#include "io_module.h"



//---------------- Private Declarations ------------------//

/// Client requested callbacks.
static io_DigInputCallback_t p_dig_callbacks[DIG_IN_END];

/// Callback for hal_module generated interrupts.
/// @param which Specific input number.
/// @param value The new value.
static void p_DigInterruptHandler(unsigned int which, bool value);



//---------------- Public API Implementation -------------//

//--------------------------------------------------------//
status_t io_InitDig(void)
{
    status_t stat = STATUS_OK;

    memset(p_dig_callbacks, 0x00, sizeof(p_dig_callbacks));

    stat = hal_RegDigInterrupt(p_DigInterruptHandler);

    return stat;
}

//--------------------------------------------------------//
status_t io_RegDigInputCallback(dig_input_t which, io_DigInputCallback_t fp)
{
    status_t stat = STATUS_OK;

    if(which < DIG_IN_END)
    {
        p_dig_callbacks[which] = fp;
    }
    else
    {
        stat = STATUS_ERROR;   
    }

    return stat;
}

//--------------------------------------------------------//
status_t io_SetDigOutput(dig_output_t which, bool value)
{
    status_t stat = STATUS_OK;

    if(which < NUM_DIG_PINS)
    {
        hal_WriteDig(which, value);
    }
    else
    {
        stat = STATUS_ERROR;   
    }

    return stat;
}

//--------------------------------------------------------//
status_t io_GetDigInput(dig_input_t which, bool* value)
{
    status_t stat = STATUS_OK;

    if(which < NUM_DIG_PINS)
    {
        stat = hal_ReadDig(which, value);
    }
    else
    {
        stat = STATUS_ERROR;   
    }

    return stat;
}

//--------------------------------------------------------//
status_t io_GetDigOutput(dig_output_t which, bool* value)
{
    status_t stat = STATUS_OK;

    if(which < NUM_DIG_PINS)
    {
        stat = hal_ReadDig(which, value);
    }
    else
    {
        stat = STATUS_ERROR;   
    }

    return stat;
}


//---------------- Private Implementation ----------------//

//--------------------------------------------------------//
void p_DigInterruptHandler(unsigned int which, bool value)
{
    if(which < NUM_DIG_PINS)
    {
        // Fire callback for registered client.
        if(p_dig_callbacks[which] != NULL)
        {
            dig_input_t din = (dig_input_t)which; // Don't ever do this!
            p_dig_callbacks[which](din, value);
        }
    }
    //else error???
}
