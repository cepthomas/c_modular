
#include <time.h>
#include <sys/time.h>
#include <string.h>

#include "hal_module.h"
#include "hal_sim.h"


//---------------- Private API Implementation ---------------//

/// Registered client callback.
static fpDigInterrupt s_digInterrupt;

/// Registered client callback.
static fpAnaInterrupt s_anaInterrupt;

/// Registered client callback.
static fpTimerInterrupt s_timerInterrupt;

/// Interrupts enabled?
static bool s_enbInterrupts;


//---------------- Private Simulator Implementation ---------------//

/// For calculating durations.
static uint64_t s_perfCtr;

//// Input pin info. Used for normal and interrupt inputs.
//typedef struct
//{
//    bool state;
//    fpDigInterrupt fpCB;
//} digInput_t;

static bool s_digInputs[NUM_DIG_INPUTS];

static bool s_digOutputs[NUM_DIG_OUTPUTS];

static int s_timerPeriod;


//---------------- Public API Implementation -------------//


//--------------------------------------------------------//
status_t hal_init(void)
{
    status_t stat = STATUS_OK;

    s_enbInterrupts = false;
    s_digInterrupt = NULL;
    s_anaInterrupt = NULL;
    s_timerInterrupt = NULL;
    s_timerPeriod = 0;
  
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
status_t hal_openSer(int channel)
{
    (void)channel;

    status_t stat = STATUS_OK;

    return stat;
}

//--------------------------------------------------------//
status_t hal_readSer(int channel, char* buff, int* num)
{
    status_t stat = STATUS_OK;

    return stat;
}

//--------------------------------------------------------//
status_t hal_writeSer(int channel, char* buff, int* num)
{
    status_t stat = STATUS_OK;
    
    return stat;    
}

//--------------------------------------------------------//
uint64_t hal_getPerfCtr(void)
{
    // Get current time/count.
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv, &tz);
    long usec = tv.tv_sec * 1000000 + tv.tv_usec;

    return usec - s_perfCtr;
}

//--------------------------------------------------------//
void hal_resetPerfCtr(void)
{
    s_perfCtr = 0;
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



///////////////////////// TODO all this below ////////////////////
// Crude write queue.
#define BUFF_LEN 128
#define NUM_PRINT_BUF 20
static char s_writeBuff[NUM_PRINT_BUF][BUFF_LEN];
static char* s_inputBuff;//[BUFF_LEN];
static int s_writeBuffIndex = 0;
// Synchronize simulated serial read.
static bool s_armRead = false;

//--------------------------------------------------------//
bool sim_cli_InjectInput(const char* input)
{
    // Clear write buffer.
    memset(s_writeBuff, 0, sizeof(s_writeBuff));
    s_writeBuffIndex = 0;

    // Copy to where cli lib expects to see it.
    strcpy(s_inputBuff, input);

    s_armRead = true;

    // Pump it.
//    bool status = cliInterpreter(0);
//    return status;

    return true;
}

//--------------------------------------------------------//
const char* sim_cli_GetOutput(int which)
{
    if(which < NUM_PRINT_BUF)
    {
        int ind = s_writeBuffIndex - which - 1;
        ind = ind < 0 ? ind + NUM_PRINT_BUF : ind;

        return s_writeBuff[ind];
    }
    else
    {
        return "Out of range!";
    }
}

//--------------------------------------------------------//
uint16_t serialWriteLine(char* pData, uint16_t serialIndex)
{
    (void)serialIndex;

    //printf(">>> %s\n", pData);

    // Store latest string.
    strncpy(s_writeBuff[s_writeBuffIndex], pData, BUFF_LEN);

    // Update index.
    s_writeBuffIndex++;
    s_writeBuffIndex %= NUM_PRINT_BUF;

    return (uint16_t)strlen(pData);
}

//--------------------------------------------------------//
bool readLineInit(int16_t serialIndex, char* lineBuf, uint16_t bufLength, char* historyBuf, uint16_t historyLines)
{
    (void)serialIndex;
    (void)bufLength;
    (void)historyBuf;
    (void)historyLines;

    s_inputBuff = lineBuf;

    return true;
}
