
#include "hal_module.h"
#include "hal_sim.h"


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
    status_t stat = STATUS_OK;

    s_timerInterrupt = fp;

    return stat;
}


//--------------------------------------------------------//
status_t hal_writePin(int pin, bool value)
{
    status_t stat = STATUS_OK;

    return stat;
}


//--------------------------------------------------------//
status_t hal_readPin(int pin, bool* value)
{
    status_t stat = STATUS_OK;

    return stat;
}


//--------------------------------------------------------//
status_t hal_writeAnalog(int channel, uint16_t value)
{
    status_t stat = STATUS_OK;

    return stat;
}

//--------------------------------------------------------//
status_t hal_readAnalog(int channel, uint16_t value)
{
    status_t stat = STATUS_OK;

    return stat;
}

//--------------------------------------------------------//
status_t hal_openSer(int channel)
{
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


#ifdef _TO_PROCESS

/////////////////////////// TO PROCESS /////////////////////////
/////////////////////////// TO PROCESS /////////////////////////
/////////////////////////// TO PROCESS /////////////////////////


/* ======================= MODULE SIMULATED FUNCTIONS - PROCBOARD === */

uint64_t timerGetTimeUSec()
{
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv, &tz);
    long usec = tv.tv_sec * 1000000 + tv.tv_usec;
    return (uint64_t)usec;
}

void caldwell_printf(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    debugLog(3, fmt, args);
}



/* ======================= PRIVATE DATA ============================= */

// Input pin info. Used for normal and interrupt inputs.
typedef struct gpioInput
{
    gpioPinState_t state;
    fpGpioCallback fpCB;
} gpioInput_t;

static gpioInput_t s_gpioInputs[INPIN_COUNT];

static gpioPinState_t s_gpioOutputs[OUTPIN_COUNT];


/* ======================= SIMULATOR API FUNCTIONS ================== */

void sim_gpio_injectInput(gpioInputPin_t pin, gpioPinState_t state)
{
    s_gpioInputs[pin].state = state;

    if(s_gpioInputs[pin].fpCB != NULL)
    {
        s_gpioInputs[pin].fpCB(pin, state);
    }
}

void sim_gpio_clearInputs()
{
    s_gpioInputs[INPIN_SWITCH_OPEN].state = PIN_CLR;
    s_gpioInputs[INPIN_SWITCH_CLOSE].state = PIN_CLR;
    s_gpioInputs[INPIN_SWITCH_STOP].state = PIN_CLR;
    s_gpioInputs[INPIN_SWITCH_UNLOCK].state = PIN_CLR;
    s_gpioInputs[INPIN_BRAKE_FAULT].state = PIN_SET;
    s_gpioInputs[INPIN_CLUTCH_FAULT].state = PIN_SET;
    s_gpioInputs[RF_GPIO_TD].state = PIN_SET;
}

void sim_gpio_clearInterrupts()
{
    for(int i = 0; i < INPIN_COUNT; i++)
    {
        s_gpioInputs[i].fpCB = NULL;
    }
}

void sim_gpio_clearOutputs()
{
    s_gpioOutputs[OUTPIN_BATTCHG_EN] = PIN_SET;
    s_gpioOutputs[OUTPIN_BRAKE_EN] = PIN_SET;
    s_gpioOutputs[OUTPIN_CLUTCH_EN] = PIN_SET;
    s_gpioOutputs[OUTPIN_MOTOR_DIR] = PIN_CLR;
    s_gpioOutputs[OUTPIN_DATA_A_EN] = PIN_CLR;
    s_gpioOutputs[OUTPIN_DATA_B_EN] = PIN_CLR;
    s_gpioOutputs[OUTPIN_DBG_1] = PIN_CLR;
    s_gpioOutputs[OUTPIN_DBG_2] = PIN_CLR;
    s_gpioOutputs[OUTPIN_LED_GRN] = PIN_SET;
    s_gpioOutputs[OUTPIN_LED_RED] = PIN_SET;
    s_gpioOutputs[OUTPIN_LED_YLW] = PIN_SET;
}


/* ======================= MODULE SIMULATED FUNCTIONS =============== */

///// Simulation of the gpio register lib function.
bool gpioManager_regPinChangeCB(gpioInputPin_t pin, fpGpioCallback fpCB)
{
    bool status = false;

    s_gpioInputs[pin].fpCB = fpCB;
    status = true;

    return status;
}

///// Simulation of the gpio register lib function.
bool gpioManager_regDebouncedCB(gpioInputPin_t pin, fpGpioCallback fpCB)
{
    // We consider them the same.
    return gpioManager_regPinChangeCB(pin, fpCB);
}

///// Simulation of the gpio read pin function.
gpioPinState_t gpioManager_getInputPin(gpioInputPin_t pin)
{
    return s_gpioInputs[pin].state;
}

//// Simulation of the gpio output function.
void gpioManager_setPin(gpioOutputPin_t pin, gpioPinState_t state)
{
    s_gpioOutputs[pin] = state;
}

//// Simulation of the gpio output function.
gpioPinState_t gpioManager_getOutputPin(gpioOutputPin_t pin)
{
    return s_gpioOutputs[pin];
}



/* ======================= PRIVATE DATA ============================= */

static uint16_t s_debugLevel;

// Crude write queue.
#define NUM_PRINT_BUF 20
static char s_writeBuff[NUM_PRINT_BUF][CLI_PRINT_BUF_LENGTH];
static int s_writeBuffIndex = 0;

// Pointer to cli internal buffer for input string.
static char* s_inputBuff;

// Synchronize simulated serial read.
static bool s_armRead = false;


/* ======================= SIMULATOR API FUNCTIONS ================== */

bool sim_cli_injectInput(const char* input)
{
    // Clear write buffer.
    memset(s_writeBuff, 0, sizeof(s_writeBuff));
    s_writeBuffIndex = 0;

    // Copy to where cli lib expects to see it.
    strcpy(s_inputBuff, input);

    s_armRead = true;

    // Pump it.
    bool status = cliInterpreter(0);

    return status;
}

const char* sim_cli_getOutput(int which)
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

/* ======================= MODULE SIMULATED FUNCTIONS =============== */

uint16_t serialWriteLine(char* pData, uint16_t serialIndex)
{
    (void)serialIndex;

    //printf(">>> %s\n", pData);

    // Store latest string.
    strncpy(s_writeBuff[s_writeBuffIndex], pData, CLI_PRINT_BUF_LENGTH);

    // Update index.
    s_writeBuffIndex++;
    s_writeBuffIndex %= NUM_PRINT_BUF;

    return (uint16_t)strlen(pData);
}

bool readLineInit(int16_t serialIndex, char* lineBuf, uint16_t bufLength, char* historyBuf, uint16_t historyLines)
{
    (void)serialIndex;
    (void)bufLength;
    (void)historyBuf;
    (void)historyLines;

    s_inputBuff = lineBuf;

    return true;
}

bool serialWriteIsBusy(uint16_t serialIndex)
{
    (void)serialIndex;

    return false;
}

bool readLineStart(uint16_t serialIndex, const char* prompt)
{
    serialWriteLine(prompt, serialIndex);
    return true;
}

char* readLineWait(uint16_t serialIndex)
{
    (void)serialIndex;

    if(s_armRead)
    {
        s_armRead = false;
        //printf("<<< %s\n", s_lineBuf);
        return (char*)s_inputBuff;
    }
    else
    {
        s_inputBuff[0] = 0;
        return NULL;
    }
}

int16_t readLineGetLineLength(uint16_t serialIndex)
{
    (void)serialIndex;

    return (int16_t)strlen(s_inputBuff);
}

void writeAndLog(bool dolog, uint16_t level, const char* format, ...)
{
    (void)dolog;
    (void)level;
    (void)format;
}

void debugLogSetLevel(uint16_t level)
{
    s_debugLevel = level;
}

uint16_t debugLogGetLevel()
{
    return s_debugLevel;
}

void debugLog(uint16_t level, const char* format, ...)
{
    if(s_debugLevel > 0 && level <= s_debugLevel)
    {
        va_list args;
        va_start(args, format);

        char buff[100];
        vsprintf(buff, format, args);
        printf(buff);

        if(format[strlen(format) - 1] != '\n')
        {
            printf("\n");
        }
    }
}

#endif // _TO_PROCESS
