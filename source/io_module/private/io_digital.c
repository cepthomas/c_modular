
#include <string.h>

#include "hal_module.h"
#include "io_module.h"



//---------------- Private --------------------------//

/// Client requested callbacks.
static fpDigInputCallback p_digInputCallbacks[DIG_IN_END];


/// Callback for hal generated interrupts.
/// @param which Specific input number.
/// @param value The new value.
static void p_digInterruptHandler(int which, bool value);


//------ Translation functions. One of many ways to do this depending on specific application.

/// Map logical to physical pin.
/// @param din Specific input.
/// @return The converted value or -1 if invalid.
static int p_inputToPin(digInput_t din);

/// Map physical pin to logical.
/// @param pin Specific pin.
/// @return The converted value or DIG_IN_END if invalid.
static digInput_t p_pinToInput(int pin);

/// Map logical to physical pin.
/// @param dout Specific output.
/// @return The converted value or -1 if invalid.
static int p_outputToPin(digOutput_t dout);

/// Map physical pin to logical.
/// @param pin Specific pin.
/// @return The converted value or DIG_OUT_END if invalid.
static digOutput_t p_pinToOutput(int pin);


//---------------- Public API Implementation -------------//

//--------------------------------------------------------//
status_t io_init(void)
{
    status_t stat = STATUS_OK;

    memset(p_digInputCallbacks, 0x00, sizeof(p_digInputCallbacks));

    stat = hal_regDigInterrupt(p_digInterruptHandler);

    p_pinToOutput(1); // just to shut up compiler

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

    int pin = p_outputToPin(which);

    if(pin != -1)
    {
        hal_writePin(pin, value);
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

    int pin = p_inputToPin(which);

    if(pin != -1)
    {
        stat = hal_readPin(pin, value);
    }
    else
    {
        stat = STATUS_ERROR;   
    }

    return stat;
}



//---------------- Private --------------------------//

//--------------------------------------------------------//
void p_digInterruptHandler(int which, bool value)
{
    digInput_t din = p_pinToInput(which);

    if(din != DIG_IN_END)
    {
        // Fire callback for registered client.
        if(p_digInputCallbacks[which] != NULL)
        {
            p_digInputCallbacks[which](din, value);
        }
    }
    //else error???
}

//------ Translation functions. One of many ways to do this depending on specific application.

//--------------------------------------------------------//
int p_inputToPin(digInput_t din)
{
    int pin = -1;

    switch(din)
    {
        case DIG_IN_BUTTON1: pin = 2; break;
        case DIG_IN_BUTTON2: pin = 5; break;
        case DIG_IN_BUTTON3: pin = 1; break;
        case DIG_IN_SWITCH1: pin = 9; break;
        case DIG_IN_SWITCH2: pin = 7; break;
        default:  pin = -1; break;
    }

    return pin;    
}

//--------------------------------------------------------//
digInput_t p_pinToInput(int pin)
{
    digInput_t din = DIG_IN_END;

    switch(pin)
    {
        case 2: din = DIG_IN_BUTTON1; break;
        case 5: din = DIG_IN_BUTTON2; break;
        case 1: din = DIG_IN_BUTTON3; break;
        case 9: din = DIG_IN_SWITCH1; break;
        case 7: din = DIG_IN_SWITCH2; break;
        default:  din = DIG_IN_END;   break;
    }
    
    return din;
}

//--------------------------------------------------------//
int p_outputToPin(digOutput_t dout)
{
    int pin = -1;

    switch(dout)
    {
        case DIG_OUT_LED1:  pin = 1; break;
        case DIG_OUT_LED2:  pin = 3; break;
        case DIG_OUT_RELAY: pin = 6; break;
        default:  pin = -1; break;
    }

    return pin;    
}

//--------------------------------------------------------//
digOutput_t p_pinToOutput(int pin)
{
   digOutput_t dout = DIG_OUT_END;

   switch(pin)
   {
       case 1: dout = DIG_OUT_LED1; break;
       case 3: dout = DIG_OUT_LED2; break;
       case 6: dout = DIG_OUT_RELAY; break;
       default: dout = DIG_OUT_END;   break;
   }
    
   return dout;
}
