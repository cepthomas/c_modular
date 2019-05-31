
#include "hal_module.h"


// Definition of the the behavior of the "real" board.
// This is just a stub as actual implementation is dependent on the 
// application-specific hardware. Yours will be completely different.


//---------------- Private --------------------------//

/// Registered client callback.
static fpDigInterrupt s_digInterrupt;

/// Registered client callback.
static fpAnaInterrupt s_anaInterrupt;

/// Registered client callback.
static fpTimerInterrupt s_timerInterrupt;

/// Interrupts enabled?
static bool s_enbInterrupts;


//---------------- Public API Implementation -------------//


//--------------------------------------------------------//
status_t hal_init(void)
{
    status_t stat = STATUS_OK;

    s_enbInterrupts = false;
    s_digInterrupt = NULL;
    s_anaInterrupt = NULL;
    s_timerInterrupt = NULL;
  
    return stat;
}

//--------------------------------------------------------//
status_t hal_enbInterrupts(bool enb)
{
    status_t stat = STATUS_OK;

    s_enbInterrupts = enb;

    return stat;
}

//--------------------------------------------------------//
status_t hal_regDigInterrupt(fpDigInterrupt fp)
{
    status_t stat = STATUS_OK;

    s_digInterrupt = fp;

    return stat;
}


//--------------------------------------------------------//
status_t hal_regAnaInterrupt(fpAnaInterrupt fp)
{
    status_t stat = STATUS_OK;

    s_anaInterrupt = fp;

    return stat;
}

//--------------------------------------------------------//
status_t hal_regTimerInterrupt(int when, fpTimerInterrupt fp)
{
    (void)when;

    status_t stat = STATUS_OK;

    s_timerInterrupt = fp;

    return stat;
}


//--------------------------------------------------------//
status_t hal_writePin(int pin, bool value)
{
    (void)pin;
    (void)value;

    status_t stat = STATUS_OK;

    return stat;
}


//--------------------------------------------------------//
status_t hal_readPin(int pin, bool* value)
{
    (void)pin;
    (void)value;

    status_t stat = STATUS_OK;

    return stat;
}


//--------------------------------------------------------//
status_t hal_writeAnalog(int channel, uint16_t value)
{
    (void)channel;
    (void)value;

    status_t stat = STATUS_OK;

    return stat;
}

//--------------------------------------------------------//
status_t hal_readAnalog(int channel, uint16_t value)
{
    (void)channel;
    (void)value;

    status_t stat = STATUS_OK;

    return stat;
}

//--------------------------------------------------------//
status_t hal_openSer(int channel)
{
    (void)channel;

    status_t stat = STATUS_OK;

    return stat;
}

//--------------------------------------------------------//
status_t hal_readSer(int channel, char* buff, int* num)
{
    (void)channel;
    (void)buff;
    (void)num;

    status_t stat = STATUS_OK;

    return stat;
}

//--------------------------------------------------------//
status_t hal_writeSer(int channel, char* buff, int* num)
{
    (void)channel;
    (void)buff;
    (void)num;

    status_t stat = STATUS_OK;
    
    return stat;    
}
