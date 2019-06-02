
#include <string.h>

#include "exec_module.h"
#include "common_module.h"
#include "hal_module.h"
#include "io_module.h"
#include "cli_module.h"

// This is a bare bones demonstration application to show how the pieces-parts play together.


//---------------- Private --------------------------//

#define CLI_PORT 0
#define SYS_TICK_MSEC 10

/// Status.
static bool s_running;

/// Status.
static bool s_relayOn;

/// CLI receive buffer.
static char s_rxBuf[CLI_BUFF_LEN];

/// CLI send buffer.
static char s_txBuf[CLI_BUFF_LEN];

/// Current tick.
static int s_tick;

/// System tick timer.
static void s_timerHandler(void);

/// Input interrupt handler.
static void s_digInput(digInput_t which, bool value);

/// Input interrupt handler.
static void s_anaInput(anaInput_t which, uint16_t value);

/// Macro to minimize boilerplate.
#define CHECKED_FUNC(_stat, _func, ...) \
{ \
    _stat = _func(__VA_ARGS__); \
    if(_stat != STATUS_OK) \
    { \
        common_log(0, "%s(%d) %s", __FILE__, __LINE__, #_func); \
    } \
}


//---------------- Public API Implementation -------------//

//--------------------------------------------------------//
status_t exec_init(void)
{
    status_t stat = STATUS_OK;

    // Init memory.
    memset(s_rxBuf, 0x00, sizeof(s_rxBuf));
    memset(s_txBuf, 0x00, sizeof(s_txBuf));

    s_running = false;
    s_relayOn = false;
    s_tick = 0;

    // Init modules.
    common_setLogLevel(1);
    CHECKED_FUNC(stat, common_init);
    CHECKED_FUNC(stat, hal_init);
    CHECKED_FUNC(stat, io_init);
    CHECKED_FUNC(stat, cli_init);

    // Set up all your board-specific stuff.
    CHECKED_FUNC(stat, hal_regTimerInterrupt, SYS_TICK_MSEC, s_timerHandler);
    CHECKED_FUNC(stat, hal_serOpen, CLI_PORT);

    // Register for input interrupts.
    CHECKED_FUNC(stat, io_regDigInputCallback, DIG_IN_BUTTON1, s_digInput);
    CHECKED_FUNC(stat, io_regDigInputCallback, DIG_IN_BUTTON2, s_digInput);
    CHECKED_FUNC(stat, io_regDigInputCallback, DIG_IN_BUTTON3, s_digInput);
    CHECKED_FUNC(stat, io_regDigInputCallback, DIG_IN_SWITCH1, s_digInput);
    CHECKED_FUNC(stat, io_regDigInputCallback, DIG_IN_SWITCH2, s_digInput);
    CHECKED_FUNC(stat, io_regAnaInputCallback, ANA_IN_TEMP, s_anaInput);
    CHECKED_FUNC(stat, io_regAnaInputCallback, ANA_IN_VELOCITY, s_anaInput);

    // Init outputs.
    CHECKED_FUNC(stat, io_setDigOutput, DIG_OUT_LED1, DIG_ON);
    CHECKED_FUNC(stat, io_setDigOutput, DIG_OUT_LED2, DIG_OFF);
    CHECKED_FUNC(stat, io_setDigOutput, DIG_OUT_RELAY, DIG_OFF);
    CHECKED_FUNC(stat, io_setAnaOutput, ANA_OUT_PRESSURE, 80);

    return stat;
}

//--------------------------------------------------------//
status_t exec_run(void)
{
    status_t stat = STATUS_OK;

    // Let her rip!
    hal_enbInterrupts(true);
    s_running = true;

    while(s_running)
    {
        // Forever loop.
    }

    hal_enbInterrupts(false);

    return stat;
}

//--------------------------------------------------------//
status_t exec_exit(void)
{
    status_t stat = STATUS_OK;

    s_running = false;
    
    return stat;
}



//---------------- Private --------------------------//

//--------------------------------------------------------//
void s_timerHandler(void)
{
    // This arrives every 10 msec.
    // Do the real work of the application.
    s_tick++;

    if(s_tick % 50 == 0)
    {
        // Poll cli.
        status_t stat = STATUS_OK;

        CHECKED_FUNC(stat, hal_serReadLine, CLI_PORT, s_rxBuf, CLI_BUFF_LEN);

        if(strlen(s_rxBuf) > 0)
        {
            // Got something. Give to cli to handle.
            CHECKED_FUNC(stat, cli_process, s_rxBuf, s_txBuf);
            CHECKED_FUNC(stat, hal_serWriteLine, CLI_PORT, s_txBuf);
        }
    }

    if(s_tick % 250 == 0)
    {
        // Other periodic stuff.
        s_relayOn = !s_relayOn;
        io_setDigOutput(DIG_OUT_RELAY, s_relayOn);
    }
}

//--------------------------------------------------------//
void s_digInput(digInput_t which, bool value)
{
    (void)which;
    (void)value;

    // Real simple logic.
    switch(which)
    {
        case DIG_IN_BUTTON1:
            io_setDigOutput(DIG_OUT_LED1, value);
            break;

        case DIG_IN_BUTTON2:
            break;

        case DIG_IN_BUTTON3:
            io_setDigOutput(DIG_OUT_LED2, !value);
            break;

        case DIG_IN_SWITCH1:
            break;

        case DIG_IN_SWITCH2:
            break;

        default:
            break;
    }
}

//--------------------------------------------------------//
void s_anaInput(anaInput_t which, uint16_t value)
{
    (void)which;
    (void)value;
}
