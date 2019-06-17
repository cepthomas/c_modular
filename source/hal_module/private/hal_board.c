
#include "hal_module.h"


// Definition of the the behavior of the "real" board.
// This is just a stub as actual implementation is dependent on the 
// application-specific hardware. Yours will be completely different.


//---------------- Private --------------------------//

/// Registered client callback.
static fpDigInterrupt p_digInterrupt;

/// Registered client callback.
static fpAnaInterrupt p_anaInterrupt;

/// Registered client callback.
static fpTimerInterrupt p_timerInterrupt;

/// Interrupts enabled?
static bool p_enbInterrupts;


//---------------- Public API Implementation -------------//

//--------------------------------------------------------//
status_t hal_init(void)
{
    status_t stat = STATUS_OK;

    p_enbInterrupts = false;
    p_digInterrupt = NULL;
    p_anaInterrupt = NULL;
    p_timerInterrupt = NULL;
  
    return stat;
}

//--------------------------------------------------------//
status_t hal_destroy(void)
{
    status_t stat = STATUS_OK;
  
    return stat;
}

//--------------------------------------------------------//
status_t hal_enbInterrupts(bool enb)
{
    status_t stat = STATUS_OK;

    p_enbInterrupts = enb;

    return stat;
}

//--------------------------------------------------------//
status_t hal_log(const char* txt)
{
    status_t stat = STATUS_OK;

    printf("%s", txt);

    return stat;
}

//--------------------------------------------------------//
status_t hal_regDigInterrupt(fpDigInterrupt fp)
{
    status_t stat = STATUS_OK;

    p_digInterrupt = fp;

    return stat;
}

//--------------------------------------------------------//
status_t hal_regAnaInterrupt(fpAnaInterrupt fp)
{
    status_t stat = STATUS_OK;

    p_anaInterrupt = fp;

    return stat;
}

//--------------------------------------------------------//
status_t hal_regTimerInterrupt(unsigned int when, fpTimerInterrupt fp)
{
    (void)when;

    status_t stat = STATUS_OK;

    p_timerInterrupt = fp;

    return stat;
}

//--------------------------------------------------------//
uint64_t hal_getCurrentUsec(void)
{
    return 999;
}

//--------------------------------------------------------//
status_t hal_writeDig(unsigned int pin, bool value)
{
    (void)pin;
    (void)value;

    status_t stat = STATUS_OK;

    return stat;
}

//--------------------------------------------------------//
status_t hal_readDig(unsigned int pin, bool* value)
{
    (void)pin;
    (void)value;

    status_t stat = STATUS_OK;

    return stat;
}

//--------------------------------------------------------//
status_t hal_writeAnalog(unsigned int channel, uint16_t value)
{
    (void)channel;
    (void)value;

    status_t stat = STATUS_OK;

    return stat;
}

//--------------------------------------------------------//
status_t hal_readAnalog(unsigned int channel, uint16_t value)
{
    (void)channel;
    (void)value;

    status_t stat = STATUS_OK;

    return stat;
}

//--------------------------------------------------------//
status_t hal_serOpen(unsigned int channel)
{
    (void)channel;

    status_t stat = STATUS_OK;

    return stat;
}

//--------------------------------------------------------//
status_t hal_serReadLine(unsigned int channel, char* buff, int num)
{
    (void)channel;
    (void)buff;
    (void)num;

    status_t stat = STATUS_OK;

    return stat;
}

//--------------------------------------------------------//
status_t hal_serWriteLine(unsigned int channel, char* buff)
{
    (void)channel;
    (void)buff;

    status_t stat = STATUS_OK;
    
    return stat;    
}
