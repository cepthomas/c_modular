
#include <time.h>
#include <sys/time.h>
#include <string.h>

#include "hal_module.h"
#include "hal_sim.h"



//---------------- Simulator Support ---------------------//
//---------------- Simulator Support ---------------------//
//---------------- Simulator Support ---------------------//

#define BUFF_LEN 128

/// Current digital pins. Index is pin num not enum.
static bool p_digPins[NUM_DIG_PINS];

/// Main timer period in msec.
static unsigned int p_timerPeriod;

/// Most recent serial port write.
static char p_lastSerWrite[BUFF_LEN];

/// Next simulated serial read.
static char p_nextSerRead[BUFF_LEN];

/// Most recent log write.
static char p_lastLogWrite[BUFF_LEN];

/// Registered client callback.
static fpDigInterrupt p_digInterrupt;

/// Registered client callback.
static fpAnaInterrupt p_anaInterrupt;

/// Registered client callback.
static fpTimerInterrupt p_timerInterrupt;

/// Interrupts enable on/off.
static bool p_enbInterrupts;




//---------------- API Implementation ---------------------//
//---------------- API Implementation ---------------------//
//---------------- API Implementation ---------------------//


//--------------------------------------------------------//
status_t hal_init(void)
{
    status_t stat = STATUS_OK;
    p_enbInterrupts = false;
    p_digInterrupt = NULL;
    p_anaInterrupt = NULL;
    p_timerInterrupt = NULL;
    p_timerPeriod = 0;
    memset(p_lastSerWrite, 0x00, sizeof(p_lastSerWrite));
    memset(p_nextSerRead, 0x00, sizeof(p_nextSerRead));
    memset(p_lastLogWrite, 0x00, sizeof(p_lastLogWrite));
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
    snprintf(p_lastLogWrite, BUFF_LEN, "%s", txt);
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
status_t hal_regTimerInterrupt(unsigned int period, fpTimerInterrupt fp)
{
    status_t stat = STATUS_OK;
    p_timerPeriod = period;
    p_timerInterrupt = fp;
    return stat;
}

//--------------------------------------------------------//
status_t hal_writeDig(unsigned int pin, bool value)
{
    status_t stat = STATUS_OK;
    p_digPins[pin] = value;
    return stat;
}

//--------------------------------------------------------//
status_t hal_readDig(unsigned int pin, bool* value)
{
    status_t stat = STATUS_OK;
    *value = p_digPins[pin];
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
    strcpy(buff, p_nextSerRead);
    p_nextSerRead[0] = 0;
    return stat;
}

//--------------------------------------------------------//
status_t hal_serWriteLine(unsigned int channel, char* buff)
{
    (void)channel;
    (void)buff;

    status_t stat = STATUS_OK;
    strncpy(p_lastSerWrite, buff, BUFF_LEN);
    p_lastSerWrite[0] = 0;
    return stat;    
}

//--------------------------------------------------------//
uint64_t hal_getCurrentUsec(void)
{
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv, &tz);
    long usec = tv.tv_sec * 1000000 + tv.tv_usec;
    return (uint64_t)usec;
}



//---------------- Simulator Support ---------------------//
//---------------- Simulator Support ---------------------//
//---------------- Simulator Support ---------------------//


//--------------------------------------------------------//
void hal_sim_clearDigPins()
{
    for(int i = 0; i < NUM_DIG_PINS; i++)
    {
        p_digPins[i] = false;
    }
}

//--------------------------------------------------------//
void hal_sim_injectDigInput(unsigned int pin, bool state)
{
    p_digPins[pin] = state;

    if(p_digInterrupt != NULL)
    {
        p_digInterrupt(pin, state);
    }
}

//--------------------------------------------------------//
bool hal_sim_getDigPin(unsigned int pin)
{
    return p_digPins[pin];
}

//--------------------------------------------------------//
const char* hal_sim_getLastSerWrite()
{
    return p_lastSerWrite;
}

//--------------------------------------------------------//
const char* hal_sim_getLastLogWrite()
{
    return p_lastLogWrite;
}

//--------------------------------------------------------//
void hal_sim_setNextSerRead(const char* s)
{
    strncpy(p_nextSerRead, s, BUFF_LEN);
}

//--------------------------------------------------------//
const char* hal_sim_getNextSerRead(void)
{
    return p_nextSerRead;
}

//--------------------------------------------------------//
void hal_sim_timerTick()
{
    p_timerInterrupt();   
}
