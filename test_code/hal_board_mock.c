
#include <time.h>
#include <sys/time.h>
#include <string.h>

#include "hal_module.h"
#include "hal_board_mock.h"


// Mock version of the hal board. This is an overly simple brute force approach.
// For anything more complicated, you should use fff or cmock instead.



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
static hal_DigInterrupt_t p_digInterrupt;

/// Registered client callback.
static hal_AnaInterrupt_t p_anaInterrupt;

/// Registered client callback.
static hal_TimerInterrupt_t p_timerInterrupt;

/// Interrupts enable on/off.
static bool p_enbInterrupts;


//---------------- API Implementation ---------------------//


//--------------------------------------------------------//
int hal_Init(void)
{
    int stat = STAT_PASS;
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
int hal_Destroy(void)
{
    int stat = STAT_PASS;
    return stat;
}

//--------------------------------------------------------//
int hal_EnbInterrupts(bool enb)
{
    int stat = STAT_PASS;
    p_enbInterrupts = enb;
    return stat;
}

//--------------------------------------------------------//
int hal_Log(const char* txt)
{
    int stat = STAT_PASS;
    snprintf(p_lastLogWrite, BUFF_LEN, "%s", txt);
    return stat;
}

//--------------------------------------------------------//
int hal_RegDigInterrupt(hal_DigInterrupt_t fp)
{
    int stat = STAT_PASS;
    p_digInterrupt = fp;
    return stat;
}

//--------------------------------------------------------//
int hal_RegAnaInterrupt(hal_AnaInterrupt_t fp)
{
    int stat = STAT_PASS;
    p_anaInterrupt = fp;
    return stat;
}

//--------------------------------------------------------//
int hal_RegTimerInterrupt(unsigned int period, hal_TimerInterrupt_t fp)
{
    int stat = STAT_PASS;
    p_timerPeriod = period;
    p_timerInterrupt = fp;
    return stat;
}

//--------------------------------------------------------//
int hal_WriteDig(unsigned int pin, bool value)
{
    int stat = STAT_PASS;
    p_digPins[pin] = value;
    return stat;
}

//--------------------------------------------------------//
int hal_ReadDig(unsigned int pin, bool* value)
{
    int stat = STAT_PASS;
    *value = p_digPins[pin];
    return stat;
}

//--------------------------------------------------------//
int hal_writeAnalog(unsigned int channel, uint16_t value)
{
    (void)channel;
    (void)value;

    int stat = STAT_PASS;
    return stat;
}

//--------------------------------------------------------//
int hal_readAnalog(unsigned int channel, uint16_t value)
{
    (void)channel;
    (void)value;

    int stat = STAT_PASS;
    return stat;
}

//--------------------------------------------------------//
int hal_SerOpen(unsigned int channel)
{
    (void)channel;

    int stat = STAT_PASS;
    return stat;
}

//--------------------------------------------------------//
int hal_SerReadLine(unsigned int channel, char* buff, int num)
{
    (void)channel;
    (void)buff;
    (void)num;

    int stat = STAT_PASS;
    strcpy(buff, p_nextSerRead);
    p_nextSerRead[0] = 0;
    return stat;
}

//--------------------------------------------------------//
int hal_SerWriteLine(unsigned int channel, char* buff)
{
    (void)channel;
    (void)buff;

    int stat = STAT_PASS;
    strncpy(p_lastSerWrite, buff, BUFF_LEN);
    p_lastSerWrite[0] = 0;
    return stat;    
}

//--------------------------------------------------------//
uint64_t hal_GetCurrentUsec(void)
{
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv, &tz);
    long usec = tv.tv_sec * 1000000 + tv.tv_usec;
    return (uint64_t)usec;
}


//---------------- Mock Support ---------------------//


//--------------------------------------------------------//
void hal_mock_clearDigPins()
{
    for(int i = 0; i < NUM_DIG_PINS; i++)
    {
        p_digPins[i] = false;
    }
}

//--------------------------------------------------------//
void hal_mock_injectDigInput(unsigned int pin, bool state)
{
    p_digPins[pin] = state;

    if(p_digInterrupt != NULL)
    {
        p_digInterrupt(pin, state);
    }
}

//--------------------------------------------------------//
bool hal_mock_getDigPin(unsigned int pin)
{
    return p_digPins[pin];
}

//--------------------------------------------------------//
const char* hal_mock_getLastSerWrite()
{
    return p_lastSerWrite;
}

//--------------------------------------------------------//
const char* hal_mock_getLastLogWrite()
{
    return p_lastLogWrite;
}

//--------------------------------------------------------//
void hal_mock_setNextSerRead(const char* s)
{
    strncpy(p_nextSerRead, s, BUFF_LEN);
}

//--------------------------------------------------------//
const char* hal_mock_getNextSerRead(void)
{
    return p_nextSerRead;
}

//--------------------------------------------------------//
void hal_mock_timerTick()
{
    p_timerInterrupt();   
}
