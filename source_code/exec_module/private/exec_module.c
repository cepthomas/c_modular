
#include <string.h>

#include "exec_module.h"
#include "common_module.h"
#include "hal_module.h"
#include "io_module.h"
#include "cli_module.h"

// This is a bare bones demonstration application to show how the pieces-parts play together.


//---------------- Private Declarations ------------------//

#define CLI_PORT 0
static const int SYS_TICK_MSEC = 10;

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
int exec_Init(void)
{
    int stat = STAT_PASS;

    // Init memory.
    memset(p_rx_buf, 0x00, sizeof(p_rx_buf));
    memset(p_tx_buf, 0x00, sizeof(p_tx_buf));

    p_running = false;
    p_relay_on = false;
    p_tick = 0;

    // Init modules.
    stat |= common_Init();
    stat |= hal_Init();
    stat |= io_Init();
    stat |= cli_Init();

    // Set up all your board-specific stuff.
    stat |= hal_RegTimerInterrupt(SYS_TICK_MSEC, p_TimerHandler);
    stat |= hal_SerOpen(CLI_PORT);

    // Register for input interrupts.
    stat |= io_RegDigInputCallback(DIG_IN_BUTTON1, p_DigInput);
    stat |= io_RegDigInputCallback(DIG_IN_BUTTON2, p_DigInput);
    stat |= io_RegDigInputCallback(DIG_IN_BUTTON3, p_DigInput);
    stat |= io_RegDigInputCallback(DIG_IN_SWITCH1, p_DigInput);
    stat |= io_RegDigInputCallback(DIG_IN_SWITCH2, p_DigInput);
    stat |= io_RegAnaInputCallback(ANA_IN_TEMP, p_AnaInput);
    stat |= io_RegAnaInputCallback(ANA_IN_VELOCITY, p_AnaInput);

    // Init outputs.
    stat |= io_SetDigOutput(DIG_OUT_LED1, DIG_ON);
    stat |= io_SetDigOutput(DIG_OUT_LED2, DIG_OFF);
    stat |= io_SetDigOutput(DIG_OUT_RELAY, DIG_OFF);
    stat |= io_SetAnaOutput(ANA_OUT_PRESSURE, 80);

    return stat;
}

//--------------------------------------------------------//
int exec_Run(void)
{
    int stat = STAT_PASS;

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
int exec_Destroy(void)
{
    int stat = STAT_PASS;
    p_running = false;

    stat = common_Destroy();
    stat = hal_Destroy();
    stat = io_Destroy();
    stat = cli_Destroy();
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
        int stat = hal_SerReadLine(CLI_PORT, p_rx_buf, CLI_BUFF_LEN);

        if(stat == STAT_PASS && strlen(p_rx_buf) > 0)
        {
            // Got something. Give to cli to handle.
            stat = cli_Process(p_rx_buf, p_tx_buf);
            stat = hal_SerWriteLine(CLI_PORT, p_tx_buf);
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
