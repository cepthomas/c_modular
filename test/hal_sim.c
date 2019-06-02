
#include <time.h>
#include <sys/time.h>
#include <string.h>

#include "hal_module.h"
#include "hal_sim.h"



//---------------- Simulator Implementation ---------------//

#define BUFF_LEN 128

/// Current digital inputs.
static bool s_digInputs[NUM_DIG_INPUTS]; //TODO index is pin num not enum!

/// Current digital outputs.
static bool s_digOutputs[NUM_DIG_OUTPUTS]; //TODO index is pin num not enum!

/// Main timer period in msec.
static int s_timerPeriod;

/// Most recent serial port write.
static char s_lastSerWrite[BUFF_LEN];

/// Next simulated serial read.
static char s_nextSerRead[BUFF_LEN];

/// Most recent log write.
static char s_lastLogWrite[BUFF_LEN];


//---------------- API Implementation ---------------------//

/// Registered client callback.
static fpDigInterrupt s_digInterrupt;

/// Registered client callback.
static fpAnaInterrupt s_anaInterrupt;

/// Registered client callback.
static fpTimerInterrupt s_timerInterrupt;

/// Interrupts enable on/off.
static bool s_enbInterrupts;

//--------------------------------------------------------//
status_t hal_init(void)
{
    status_t stat = STATUS_OK;

    s_enbInterrupts = false;
    s_digInterrupt = NULL;
    s_anaInterrupt = NULL;
    s_timerInterrupt = NULL;
    s_timerPeriod = 0;
  
    memset(s_lastSerWrite, 0x00, sizeof(s_lastSerWrite));
    memset(s_nextSerRead, 0x00, sizeof(s_nextSerRead));
    memset(s_lastLogWrite, 0x00, sizeof(s_lastLogWrite));

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
status_t hal_pump() //TODO
{
    status_t stat = STATUS_OK;

    return stat;
}

//--------------------------------------------------------//
status_t hal_log(const char* txt)
{
    sprintf(s_lastLogWrite, "%s\n", txt);
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
status_t hal_regTimerInterrupt(int period, fpTimerInterrupt fp)
{
    status_t stat = STATUS_OK;

    s_timerPeriod = period;
    s_timerInterrupt = fp;

    return stat;
}

//--------------------------------------------------------//
status_t hal_writePin(int pin, bool value)
{
    status_t stat = STATUS_OK;
    s_digOutputs[pin] = value;
    return stat;
}

//--------------------------------------------------------//
status_t hal_readPin(int pin, bool* value)
{
    status_t stat = STATUS_OK;
    *value = s_digInputs[pin];
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
status_t hal_serOpen(int channel)
{
    (void)channel;

    status_t stat = STATUS_OK;

    return stat;
}

//--------------------------------------------------------//
status_t hal_serReadLine(int channel, char* buff, int num)
{
    (void)channel;
    (void)buff;
    (void)num;

    strncpy(buff, s_nextSerRead, BUFF_LEN);
    s_nextSerRead[0] = 0;

    status_t stat = STATUS_OK;

    return stat;
}

//--------------------------------------------------------//
status_t hal_serWriteLine(int channel, char* buff)
{
    (void)channel;
    (void)buff;

    strncpy(s_lastSerWrite, buff, BUFF_LEN);
    s_lastSerWrite[0] = 0;

    status_t stat = STATUS_OK;
    
    return stat;    
}

//--------------------------------------------------------//
uint64_t s_getCurrentUsec(void)
{
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv, &tz);
    long usec = tv.tv_sec * 1000000 + tv.tv_usec;
    return usec;
}


//---------------- Simulator Implementation -------------//


//--------------------------------------------------------//
void sim_io_clearInputs()
{
    for(int i = 0; i < NUM_DIG_INPUTS; i++)
    {
        s_digInputs[i] = false;
    }
}

//--------------------------------------------------------//
void sim_io_clearOutputs()
{
    for(int i = 0; i < NUM_DIG_OUTPUTS; i++)
    {
        s_digOutputs[i] = false;
    }
}

//--------------------------------------------------------//
void sim_io_injectInput(int pin, bool state)
{
    s_digInputs[pin] = state;

    if(s_digInterrupt != NULL)
    {
        s_digInterrupt(pin, state);
    }
}

//--------------------------------------------------------//
bool sim_io_getOutputPin(int pin)
{
    return s_digOutputs[pin];
}

//--------------------------------------------------------//
const char* sim_getLastSerWrite()
{
    return s_lastSerWrite;
}

//--------------------------------------------------------//
const char* sim_getLastLogWrite()
{
    return s_lastLogWrite;
}

//--------------------------------------------------------//
void sim_setNextSerRead(const char* s)
{
    strncpy(s_nextSerRead, s, BUFF_LEN);
}
