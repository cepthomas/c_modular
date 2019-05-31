
#include <string.h>

#include "exec_module.h"
#include "common_module.h"
#include "hal_module.h"
#include "io_module.h"
#include "cli_module.h"

// This is a bare bones demonstration application to show the pieces-parts
// play together.


//---------------- Private --------------------------//

#define CLI_PORT 0
#define SYS_TICK 10 // msec

/// Status.
static bool s_running;

/// Status.
static bool s_relayOn;

/// CLI receive buffer.
static char s_cliRxBuf[CLI_BUFF_LEN];

/// CLI send buffer.
static char s_cliTxBuf[CLI_BUFF_LEN];

/// System tick timer.
static void s_timerHandler(void);

/// Current tick.
static int s_tick;

/// Input interrupt handler.
static void s_digInput(digInput_t which, bool value);

/// Input interrupt handler.
static void s_anaInput(anaInput_t which, uint16_t value);


#define CHECKED_FUNC(_stat, _func, ...) \
{ \
    _stat = _func(__VA_ARGS__); \
    if(_stat != STATUS_OK) \
    { \
        common_debugLog(0, "%s(%d) %s", __FILE__, __LINE__, #_func); \
    } \
}

// #define eprintf(format, ...) fprintf (stderr, format __VA_OPT__(,) __VA_ARGS__)


//---------------- Public API Implementation -------------//

//--------------------------------------------------------//
status_t exec_init(void)
{
    status_t stat = STATUS_OK;

    // Init memory.
    memset(s_cliRxBuf, 0x00, sizeof(s_cliRxBuf));
    memset(s_cliTxBuf, 0x00, sizeof(s_cliTxBuf));

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
    CHECKED_FUNC(stat, hal_regTimerInterrupt, SYS_TICK, s_timerHandler);
    CHECKED_FUNC(stat, hal_openSer, CLI_PORT);

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

    while(s_running)
    {
        // do nothing
    }

    return stat;
}

//---------------- Private --------------------------//

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

//--------------------------------------------------------//
void s_timerHandler(void)
{
    // Arrives every 10 msec.
    s_tick++;

    if(s_tick % 50 == 0)
    {
        // Poll cli. TODO


    }

    if(s_tick % 250 == 0)
    {
        // Other stuff.
        s_relayOn = !s_relayOn;
        io_setDigOutput(DIG_OUT_RELAY, s_relayOn);
    }

    if(s_tick >= 1000)
    {
        s_running = false;
    }
}
