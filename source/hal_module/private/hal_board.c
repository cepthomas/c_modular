
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
int hal_Init(void)
{
    int stat = RS_PASS;

    p_enb_interrupts = false;
    p_dig_interrupt = NULL;
    p_ana_interrupt = NULL;
    p_timer_interrupt = NULL;
  
    return stat;
}

//--------------------------------------------------------//
int hal_Destroy(void)
{
    int stat = RS_PASS;
  
    return stat;
}

//--------------------------------------------------------//
int hal_EnbInterrupts(bool enb)
{
    int stat = RS_PASS;

    p_enb_interrupts = enb;

    return stat;
}

//--------------------------------------------------------//
int hal_Log(const char* txt)
{
    int stat = RS_PASS;

    // Fake logger.
    printf("LOG:%s", txt);

    return stat;
}

//--------------------------------------------------------//
int hal_RegDigInterrupt(hal_DigInterrupt_t fp)
{
    int stat = RS_PASS;

    p_dig_interrupt = fp;

    return stat;
}

//--------------------------------------------------------//
int hal_RegAnaInterrupt(hal_AnaInterrupt_t fp)
{
    int stat = RS_PASS;

    p_ana_interrupt = fp;

    return stat;
}

//--------------------------------------------------------//
int hal_RegTimerInterrupt(unsigned int when, hal_TimerInterrupt_t fp)
{
    (void)when;

    int stat = RS_PASS;

    p_timer_interrupt = fp;

    return stat;
}

//--------------------------------------------------------//
uint64_t hal_GetCurrentUsec(void)
{
    return 999;
}

//--------------------------------------------------------//
int hal_WriteDig(unsigned int pin, bool value)
{
    (void)pin;
    (void)value;

    int stat = RS_PASS;

    return stat;
}

//--------------------------------------------------------//
int hal_ReadDig(unsigned int pin, bool* value)
{
    (void)pin;
    (void)value;

    int stat = RS_PASS;

    return stat;
}

//--------------------------------------------------------//
int hal_writeAnalog(unsigned int channel, uint16_t value)
{
    (void)channel;
    (void)value;

    int stat = RS_PASS;

    return stat;
}

//--------------------------------------------------------//
int hal_readAnalog(unsigned int channel, uint16_t value)
{
    (void)channel;
    (void)value;

    int stat = RS_PASS;

    return stat;
}

//--------------------------------------------------------//
int hal_SerOpen(unsigned int channel)
{
    (void)channel;

    int stat = RS_PASS;

    return stat;
}

//--------------------------------------------------------//
int hal_SerReadLine(unsigned int channel, char* buff, int num)
{
    (void)channel;
    (void)buff;
    (void)num;

    int stat = RS_PASS;

    return stat;
}

//--------------------------------------------------------//
int hal_SerWriteLine(unsigned int channel, char* buff)
{
    (void)channel;
    (void)buff;

    int stat = RS_PASS;
    
    return stat;    
}
