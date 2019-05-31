
#include <stdio.h>
#include <string.h>

#include "pnut.h"

extern "C"
{
#include "exec_module.h"
#include "common_module.h"
#include "hal_module.h"
#include "io_module.h"
#include "cli_module.h"
}




/* ======================= TEST CASES ==================================== */

UT_SUITE(XXX_1, "Test everything.")
{
    status_t status = STATUS_OK;

    // Init modules.
    status = exec_init();
    UT_EQUAL(status, STATUS_OK);


    // status = cli_init(0);
    // UT_EQUAL(status, STATUS_OK);

    // // Allow all commands.
    // cliSetUserLevel(2);

    // // Initialize the alds db to defaults.
    // status = sim_cli_injectInput("c all reset");
    // UT_TRUE(status);

    // // Set some non-defaults first.
    // status = sim_cli_injectInput("config deb 707");
    // UT_TRUE(status);
    // status = sim_cli_injectInput("config kemeth keb");
    // UT_TRUE(status);
    // status = sim_cli_injectInput("config pmenb 1");
    // UT_TRUE(status);
    // status = sim_cli_injectInput("config pdia 1.23");
    // UT_TRUE(status);

    // // cmd > config all - dumps info for all commands
    // status = sim_cli_injectInput("config all");
    // UT_TRUE(status);
    // // The last writes. Note this changes every time a new config value is added.
    // UT_STR_EQUAL(sim_cli_getOutput(1), "deb: Motion detect debounce time in msec min:-1 max:1000 default:50 current:707");
    // UT_STR_EQUAL(sim_cli_getOutput(2), "motdir: Motor drive dir options:normal invert current:normal");
    // UT_STR_EQUAL(sim_cli_getOutput(3), "enpol: Encoder polarity options:normal invert current:invert");
    // UT_STR_EQUAL(sim_cli_getOutput(4), "pop: Position Open Full in in min:0.00 max:500.00 default:95.00 current:95.00");
}




#ifdef _TO_PROCESS

//static command_t s_lastCommand;

//static void commandCallback(command_t);

static char s_workBuff[32];

/* ======================= TEST CASES ==================================== */

UT_CASE(PBTN_1, "Test pushbuttons module.")
{
    // From SOW:
    // - Discrete switch inputs open, close, stop, and exit are active high.
    // - RF_GPIO(motion) is active low - It is pulled high on the Processor board.

    clearGpioInputs();
    clearGpioInterrupts();

    UT_STEP("Raw pushbutton presses.")
    {
        bool status = pushbuttons_init();
        UT_CHECK_TRUE(status);

        // Register a callback from the pushbutton module.
        pushbuttons_regPushbuttonChangeCB(&pushbuttonCallback);
        pushbuttons_regCommandCB(&commandCallback);

        injectGpioInput(INPIN_SWITCH_CLOSE, PIN_CLR);
        UT_CHECK_STR_EQUAL(toString(s_lastPushbutton), toString(PUSHBUTTON_CLOSE));
        UT_CHECK_STR_EQUAL(toString(s_lastState), toString(false));

        injectGpioInput(INPIN_SWITCH_UNLOCK, PIN_SET);
        UT_CHECK_STR_EQUAL(toString(s_lastPushbutton), toString(PUSHBUTTON_UNLOCK));
        UT_CHECK_STR_EQUAL(toString(s_lastState), toString(true));
        injectGpioInput(INPIN_SWITCH_UNLOCK, PIN_CLR);
        UT_CHECK_STR_EQUAL(toString(s_lastPushbutton), toString(PUSHBUTTON_UNLOCK));
        UT_CHECK_STR_EQUAL(toString(s_lastState), toString(false));
    }
    UT_STEP_END();

    UT_STEP("Pushbutton commands.")
    {
        // Simple: COMMAND_OPEN.
        injectGpioInput(INPIN_SWITCH_OPEN, PIN_SET);
        injectGpioInput(INPIN_SWITCH_OPEN, PIN_CLR);
        UT_CHECK_STR_EQUAL(toString(s_lastCommand), toString(COMMAND_OPEN));

        // Combination: COMMAND_OPEN_CLOSE.
        injectGpioInput(INPIN_SWITCH_OPEN, PIN_SET);
        injectGpioInput(INPIN_SWITCH_CLOSE, PIN_SET);
        injectGpioInput(INPIN_SWITCH_OPEN, PIN_CLR);
        injectGpioInput(INPIN_SWITCH_CLOSE, PIN_CLR);
        UT_CHECK_STR_EQUAL(toString(s_lastCommand), toString(COMMAND_OPEN_CLOSE));

        // Combination: COMMAND_OPEN_STOP.
        injectGpioInput(INPIN_SWITCH_OPEN, PIN_SET);
        injectGpioInput(INPIN_SWITCH_STOP, PIN_SET);
        injectGpioInput(INPIN_SWITCH_STOP, PIN_CLR);
        injectGpioInput(INPIN_SWITCH_OPEN, PIN_CLR);
        UT_CHECK_STR_EQUAL(toString(s_lastCommand), toString(COMMAND_OPEN_STOP));

        // Combination: COMMAND_STOP_UNLOCK.
        injectGpioInput(INPIN_SWITCH_UNLOCK, PIN_SET);
        injectGpioInput(INPIN_SWITCH_STOP, PIN_SET);
        injectGpioInput(INPIN_SWITCH_STOP, PIN_CLR);
        injectGpioInput(INPIN_SWITCH_UNLOCK, PIN_CLR);
        UT_CHECK_STR_EQUAL(toString(s_lastCommand), toString(COMMAND_STOP_UNLOCK));

        // Simple: COMMAND_STOP.
        injectGpioInput(INPIN_SWITCH_STOP, PIN_SET);
        injectGpioInput(INPIN_SWITCH_STOP, PIN_CLR);
        UT_CHECK_STR_EQUAL(toString(s_lastCommand), toString(COMMAND_STOP));

        // Nonsense combination.
        s_lastCommand = COMMAND_NONE;
        injectGpioInput(INPIN_SWITCH_UNLOCK, PIN_SET);
        injectGpioInput(INPIN_SWITCH_OPEN, PIN_SET);
        injectGpioInput(INPIN_SWITCH_OPEN, PIN_CLR);
        injectGpioInput(INPIN_SWITCH_UNLOCK, PIN_CLR);
        UT_CHECK_STR_EQUAL(toString(s_lastCommand), toString(COMMAND_NONE));
    }
    UT_STEP_END();

    UT_STEP("Motion sensor.")
    {
        injectGpioInput(RF_GPIO_TD, PIN_CLR);
        UT_CHECK_STR_EQUAL(toString(s_lastPushbutton), toString(PUSHBUTTON_MOTION));
        UT_CHECK_STR_EQUAL(toString(s_lastState), toString(true));

        injectGpioInput(RF_GPIO_TD, PIN_SET);
        UT_CHECK_STR_EQUAL(toString(s_lastPushbutton), toString(PUSHBUTTON_MOTION));
        UT_CHECK_STR_EQUAL(toString(s_lastState), toString(false));
    }
    UT_STEP_END();
}

UT_SUITE(LEDS_1, "Test setting leds.")
{
    sim_gpio_clearInputs();
    sim_gpio_clearOutputs();

    bool status = leds_init();
    UT_TRUE(status);

    // Defaults.
    UT_EQUAL(gpioManager_getOutputPin(OUTPIN_LED_GRN), PIN_SET);
    UT_EQUAL(gpioManager_getOutputPin(OUTPIN_LED_YLW), PIN_SET);
    UT_EQUAL(gpioManager_getOutputPin(OUTPIN_LED_RED), PIN_SET);

    // Set some combinations.
    leds_setLed(LED_GRN, true);
    leds_setLed(LED_YLW, false);
    leds_setLed(LED_RED, true);
    UT_EQUAL(gpioManager_getOutputPin(OUTPIN_LED_GRN), PIN_CLR);
    UT_EQUAL(gpioManager_getOutputPin(OUTPIN_LED_YLW), PIN_SET);
    UT_EQUAL(gpioManager_getOutputPin(OUTPIN_LED_RED), PIN_CLR);

    leds_setLed(LED_YLW, true);
    leds_setLed(LED_RED, false);
    UT_EQUAL(gpioManager_getOutputPin(OUTPIN_LED_GRN), PIN_CLR);
    UT_EQUAL(gpioManager_getOutputPin(OUTPIN_LED_YLW), PIN_CLR);
    UT_EQUAL(gpioManager_getOutputPin(OUTPIN_LED_RED), PIN_SET);
}

/* ======================= MODULE SIMULATION ==================================== */

// Module is telling us something happened. Store it for inspection.
void pushbuttonCallback(pushbutton_t pushbutton, bool state)
{
    s_lastPushbutton = pushbutton;
    s_lastState = state;
}

// Module is telling us something happened. Store it for inspection.
void commandCallback(command_t command)
{
    s_lastCommand = command;
}

#endif // #ifdef _TO_PROCESS
