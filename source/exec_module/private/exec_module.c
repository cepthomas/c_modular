
#include <string.h>

#include "exec_module.h"
#include "common_module.h"
#include "hal_module.h"
#include "io_module.h"
#include "cli_module.h"

// This is a bare bones demonstration application to show how the pieces-parts play together.


//---------------- Private Declarations ------------------//

#define CLI_PORT 0
#define SYS_TICK_MSEC 10

/// Status.
static bool p_running;

/// Status.
static bool p_relay_on;

/// CLI receive buffer.
static char p_rx_buf[CLI_BUFF_LEN];

/// CLI send buffer.
static char p_tx_buf[CLI_BUFF_LEN];

/// Current tick.
static int p_tick;

/// System tick timer.
static void p_TimerHandler(void);

/// Input interrupt handler.
static void p_DigInput(dig_input_t which, bool value);

/// Input interrupt handler.
static void p_AnaInput(ana_input_t which, uint16_t value);


//---------------- Public API Implementation -------------//

//--------------------------------------------------------//
status_t exec_Init(void)
{
    status_t stat = STATUS_OK;

    // Init memory.
    memset(p_rx_buf, 0x00, sizeof(p_rx_buf));
    memset(p_tx_buf, 0x00, sizeof(p_tx_buf));

    p_running = false;
    p_relay_on = false;
    p_tick = 0;

    // Init modules.
    common_SetLogLevel(1);
    CHECKED_FUNC(stat, common_Init);
    CHECKED_FUNC(stat, hal_Init);
    CHECKED_FUNC(stat, io_Init);
    CHECKED_FUNC(stat, cli_Init);

    // Set up all your board-specific stuff.
    CHECKED_FUNC(stat, hal_RegTimerInterrupt, SYS_TICK_MSEC, p_TimerHandler);
    CHECKED_FUNC(stat, hal_SerOpen, CLI_PORT);

    // Register for input interrupts.
    CHECKED_FUNC(stat, io_RegDigInputCallback, DIG_IN_BUTTON1, p_DigInput);
    CHECKED_FUNC(stat, io_RegDigInputCallback, DIG_IN_BUTTON2, p_DigInput);
    CHECKED_FUNC(stat, io_RegDigInputCallback, DIG_IN_BUTTON3, p_DigInput);
    CHECKED_FUNC(stat, io_RegDigInputCallback, DIG_IN_SWITCH1, p_DigInput);
    CHECKED_FUNC(stat, io_RegDigInputCallback, DIG_IN_SWITCH2, p_DigInput);
    CHECKED_FUNC(stat, io_RegAnaInputCallback, ANA_IN_TEMP, p_AnaInput);
    CHECKED_FUNC(stat, io_RegAnaInputCallback, ANA_IN_VELOCITY, p_AnaInput);

    // Init outputs.
    CHECKED_FUNC(stat, io_SetDigOutput, DIG_OUT_LED1, DIG_ON);
    CHECKED_FUNC(stat, io_SetDigOutput, DIG_OUT_LED2, DIG_OFF);
    CHECKED_FUNC(stat, io_SetDigOutput, DIG_OUT_RELAY, DIG_OFF);
    CHECKED_FUNC(stat, io_SetAnaOutput, ANA_OUT_PRESSURE, 80);

    return stat;
}

//--------------------------------------------------------//
status_t exec_Run(void)
{
    status_t stat = STATUS_OK;

    // Let her rip!
    hal_EnbInterrupts(true);
    p_running = true;

    while(p_running)
    {
        // Forever loop.
    }

    hal_EnbInterrupts(false);

    return stat;
}

//--------------------------------------------------------//
status_t exec_Destroy(void)
{
    status_t stat = STATUS_OK;
    p_running = false;

    CHECKED_FUNC(stat, common_Destroy);
    CHECKED_FUNC(stat, hal_Destroy);
    CHECKED_FUNC(stat, io_Destroy);
    CHECKED_FUNC(stat, cli_Destroy);
    
    return stat;
}


//---------------- Private Implementation ----------------//

//--------------------------------------------------------//
void p_TimerHandler(void)
{
    // This arrives every 10 msec.
    // Do the real work of the application.
    p_tick++;

    if(p_tick % 50 == 0)
    {
        // Poll cli.
        status_t stat = STATUS_OK;

        CHECKED_FUNC(stat, hal_SerReadLine, CLI_PORT, p_rx_buf, CLI_BUFF_LEN);

        if(strlen(p_rx_buf) > 0)
        {
            // Got something. Give to cli to handle.
            CHECKED_FUNC(stat, cli_Process, p_rx_buf, p_tx_buf);
            CHECKED_FUNC(stat, hal_SerWriteLine, CLI_PORT, p_tx_buf);
        }
    }

    if(p_tick % 250 == 0)
    {
        // Other periodic stuff.
        p_relay_on = !p_relay_on;
        io_SetDigOutput(DIG_OUT_RELAY, p_relay_on);
    }
}

//--------------------------------------------------------//
void p_DigInput(dig_input_t which, bool value)
{
    (void)which;
    (void)value;

    // Real simple logic.
    switch(which)
    {
        case DIG_IN_BUTTON1:
            io_SetDigOutput(DIG_OUT_LED1, value);
            break;

        case DIG_IN_BUTTON2:
            break;

        case DIG_IN_BUTTON3:
            io_SetDigOutput(DIG_OUT_LED2, !value);
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
void p_AnaInput(ana_input_t which, uint16_t value)
{
    (void)which;
    (void)value;
}
