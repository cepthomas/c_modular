
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
static bool p_running;

/// Status.
static bool p_relayOn;

/// CLI receive buffer.
static char p_rxBuf[CLI_BUFF_LEN];

/// CLI send buffer.
static char p_txBuf[CLI_BUFF_LEN];

/// Current tick.
static int p_tick;

/// System tick timer.
static void p_timerHandler(void);

/// Input interrupt handler.
static void p_digInput(digInput_t which, bool value);

/// Input interrupt handler.
static void p_anaInput(anaInput_t which, uint16_t value);


//---------------- Public API Implementation -------------//

//--------------------------------------------------------//
status_t exec_init(void)
{
    status_t stat = STATUS_OK;

    // Init memory.
    memset(p_rxBuf, 0x00, sizeof(p_rxBuf));
    memset(p_txBuf, 0x00, sizeof(p_txBuf));

    p_running = false;
    p_relayOn = false;
    p_tick = 0;

    // Init modules.
    common_setLogLevel(1);
    CHECKED_FUNC(stat, common_init);
    CHECKED_FUNC(stat, hal_init);
    CHECKED_FUNC(stat, io_init);
    CHECKED_FUNC(stat, cli_init);

    // Set up all your board-specific stuff.
    CHECKED_FUNC(stat, hal_regTimerInterrupt, SYS_TICK_MSEC, p_timerHandler);
    CHECKED_FUNC(stat, hal_serOpen, CLI_PORT);

    // Register for input interrupts.
    CHECKED_FUNC(stat, io_regDigInputCallback, DIG_IN_BUTTON1, p_digInput);
    CHECKED_FUNC(stat, io_regDigInputCallback, DIG_IN_BUTTON2, p_digInput);
    CHECKED_FUNC(stat, io_regDigInputCallback, DIG_IN_BUTTON3, p_digInput);
    CHECKED_FUNC(stat, io_regDigInputCallback, DIG_IN_SWITCH1, p_digInput);
    CHECKED_FUNC(stat, io_regDigInputCallback, DIG_IN_SWITCH2, p_digInput);
    CHECKED_FUNC(stat, io_regAnaInputCallback, ANA_IN_TEMP, p_anaInput);
    CHECKED_FUNC(stat, io_regAnaInputCallback, ANA_IN_VELOCITY, p_anaInput);

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
    p_running = true;

    while(p_running)
    {
        // Forever loop.
    }

    hal_enbInterrupts(false);

    return stat;
}

//--------------------------------------------------------//
status_t exec_destroy(void)
{
    status_t stat = STATUS_OK;
    p_running = false;

    CHECKED_FUNC(stat, common_destroy);
    CHECKED_FUNC(stat, hal_destroy);
    CHECKED_FUNC(stat, io_destroy);
    CHECKED_FUNC(stat, cli_destroy);
    
    return stat;
}


//---------------- Private --------------------------//

//--------------------------------------------------------//
void p_timerHandler(void)
{
    // This arrives every 10 msec.
    // Do the real work of the application.
    p_tick++;

    if(p_tick % 50 == 0)
    {
        // Poll cli.
        status_t stat = STATUS_OK;

        CHECKED_FUNC(stat, hal_serReadLine, CLI_PORT, p_rxBuf, CLI_BUFF_LEN);

        if(strlen(p_rxBuf) > 0)
        {
            // Got something. Give to cli to handle.
            CHECKED_FUNC(stat, cli_process, p_rxBuf, p_txBuf);
            CHECKED_FUNC(stat, hal_serWriteLine, CLI_PORT, p_txBuf);
        }
    }

    if(p_tick % 250 == 0)
    {
        // Other periodic stuff.
        p_relayOn = !p_relayOn;
        io_setDigOutput(DIG_OUT_RELAY, p_relayOn);
    }
}

//--------------------------------------------------------//
void p_digInput(digInput_t which, bool value)
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
void p_anaInput(anaInput_t which, uint16_t value)
{
    (void)which;
    (void)value;
}
