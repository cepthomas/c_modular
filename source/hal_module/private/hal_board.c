
#include "hal_module.h"


// Definition of the the behavior of the "real" board.
// This is just a stub as actual implementation is dependent on the 
// application-specific hardware. Yours will be completely different.


//---------------- Private Declarations ------------------//

/// Registered client callback.
static hal_DigInterrupt_t p_dig_interrupt;

/// Registered client callback.
static hal_AnaInterrupt_t p_ana_interrupt;

/// Registered client callback.
static hal_TimerInterrupt_t p_timer_interrupt;

/// Interrupts enabled?
static bool p_enb_interrupts;


//---------------- Public API Implementation -------------//

//--------------------------------------------------------//
status_t hal_Init(void)
{
    status_t stat = STATUS_OK;

    p_enb_interrupts = false;
    p_dig_interrupt = NULL;
    p_ana_interrupt = NULL;
    p_timer_interrupt = NULL;
  
    return stat;
}

//--------------------------------------------------------//
status_t hal_Destroy(void)
{
    status_t stat = STATUS_OK;
  
    return stat;
}

//--------------------------------------------------------//
status_t hal_EnbInterrupts(bool enb)
{
    status_t stat = STATUS_OK;

    p_enb_interrupts = enb;

    return stat;
}

//--------------------------------------------------------//
status_t hal_Log(const char* txt)
{
    status_t stat = STATUS_OK;

    printf("%s", txt);

    return stat;
}

//--------------------------------------------------------//
status_t hal_RegDigInterrupt(hal_DigInterrupt_t fp)
{
    status_t stat = STATUS_OK;

    p_dig_interrupt = fp;

    return stat;
}

//--------------------------------------------------------//
status_t hal_RegAnaInterrupt(hal_AnaInterrupt_t fp)
{
    status_t stat = STATUS_OK;

    p_ana_interrupt = fp;

    return stat;
}

//--------------------------------------------------------//
status_t hal_RegTimerInterrupt(unsigned int when, hal_TimerInterrupt_t fp)
{
    (void)when;

    status_t stat = STATUS_OK;

    p_timer_interrupt = fp;

    return stat;
}

//--------------------------------------------------------//
uint64_t hal_GetCurrentUsec(void)
{
    return 999;
}

//--------------------------------------------------------//
status_t hal_WriteDig(unsigned int pin, bool value)
{
    (void)pin;
    (void)value;

    status_t stat = STATUS_OK;

    return stat;
}

//--------------------------------------------------------//
status_t hal_ReadDig(unsigned int pin, bool* value)
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
status_t hal_SerOpen(unsigned int channel)
{
    (void)channel;

    status_t stat = STATUS_OK;

    return stat;
}

//--------------------------------------------------------//
status_t hal_SerReadLine(unsigned int channel, char* buff, int num)
{
    (void)channel;
    (void)buff;
    (void)num;

    status_t stat = STATUS_OK;

    return stat;
}

//--------------------------------------------------------//
status_t hal_SerWriteLine(unsigned int channel, char* buff)
{
    (void)channel;
    (void)buff;

    status_t stat = STATUS_OK;
    
    return stat;    
}
