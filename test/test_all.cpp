
#include <stdio.h>
#include <string.h>

#include "pnut.h"
//#include "test-utils.h"
//#include "formatters.h"

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


// This tests the application stuff and the cli-library interpreter code.

// When running config all command, add display of currently-set value to end of each item

// Add new config changed command, which displays lines identically to config all but only displays those configuration items whose values are modified from their defaults.


/* ======================= SHARED VARIABLES ==================================== */

//static command_t s_lastCommand;

//static void commandCallback(command_t);

static char s_workBuff[32];

/* ======================= TEST CASES ==================================== */

UT_SUITE(CLI_1, "Test configuration cli functions.")
{
    bool status = false;

    // Init modules.
    status = configuration_init();
    UT_TRUE(status);
    status = cliInit(0);
    UT_TRUE(status);

    // Allow all commands.
    cliSetUserLevel(2);

    // Initialize the alds db to defaults.
    status = sim_cli_injectInput("c all reset");
    UT_TRUE(status);

    // Set some non-defaults first.
    status = sim_cli_injectInput("config deb 707");
    UT_TRUE(status);
    status = sim_cli_injectInput("config kemeth keb");
    UT_TRUE(status);
    status = sim_cli_injectInput("config pmenb 1");
    UT_TRUE(status);
    status = sim_cli_injectInput("config pdia 1.23");
    UT_TRUE(status);

    // cmd > config all - dumps info for all commands
    status = sim_cli_injectInput("config all");
    UT_TRUE(status);
    // The last writes. Note this changes every time a new config value is added.
    UT_STR_EQUAL(sim_cli_getOutput(1), "deb: Motion detect debounce time in msec min:-1 max:1000 default:50 current:707");
    UT_STR_EQUAL(sim_cli_getOutput(2), "motdir: Motor drive dir options:normal invert current:normal");
    UT_STR_EQUAL(sim_cli_getOutput(3), "enpol: Encoder polarity options:normal invert current:invert");
    UT_STR_EQUAL(sim_cli_getOutput(4), "pop: Position Open Full in in min:0.00 max:500.00 default:95.00 current:95.00");

    // cmd > config changed - dumps info for only changed (non-default) commands
    status = sim_cli_injectInput("config changed");
    UT_TRUE(status);
    // The last writes. Note this changes every time a new config value is added.
    UT_STR_EQUAL(sim_cli_getOutput(1), "deb: Motion detect debounce time in msec min:-1 max:1000 default:50 current:707");
    UT_STR_EQUAL(sim_cli_getOutput(2), "pmenb: Party Mode Enable options:1 0 current:1");
    UT_STR_EQUAL(sim_cli_getOutput(3), "kemeth: KE Method options:kea keb current:keb");
    UT_STR_EQUAL(sim_cli_getOutput(4), "pdia: Pulley Diameter in in min:0.50 max:2.00 default:2.00 current:1.23");

    // cmd > config bad-item
    status = sim_cli_injectInput("config me-bad me-too");
    UT_TRUE(status);
    UT_STR_EQUAL(sim_cli_getOutput(1), "Invalid item: me-bad");

    // cmd > config item value - sets db item to value
    // Tests are actually done in the next chunk.
    status = sim_cli_injectInput("config egod 1.23");
    UT_TRUE(status);

    status = sim_cli_injectInput("config osp 8.34");
    UT_TRUE(status);
    UT_STR_EQUAL(sim_cli_getOutput(0), "cmd>");

    status = sim_cli_injectInput("config motdir invert");
    UT_TRUE(status);

    status = sim_cli_injectInput("config maenb 1");
    UT_TRUE(status);

    // cmd > config item - returns value for current db item
    status = sim_cli_injectInput("config egod");
    UT_TRUE(status);
    UT_STR_EQUAL(sim_cli_getOutput(1), "1.23");

    status = sim_cli_injectInput("config osp");
    UT_TRUE(status);
    UT_STR_EQUAL(sim_cli_getOutput(1), "8.34");

    status = sim_cli_injectInput("config motdir");
    UT_TRUE(status);
    UT_STR_EQUAL(sim_cli_getOutput(1), "invert");

    status = sim_cli_injectInput("config maenb");
    UT_TRUE(status);
    UT_STR_EQUAL(sim_cli_getOutput(1), "1");

    // cmd > config item reset - sets db item to its default
    status = sim_cli_injectInput("config egod reset");
    // Read back.
    status = sim_cli_injectInput("config egod");
    UT_STR_EQUAL(sim_cli_getOutput(1), "4.00");

    // Reset everything.
    status = sim_cli_injectInput("config osp reset");

    // Read back value.
    status = sim_cli_injectInput("config osp");
    UT_STR_EQUAL(sim_cli_getOutput(1), "6.00");

    // Write value.
    status = sim_cli_injectInput("config motdir reset");

    // Read back.
    status = sim_cli_injectInput("config motdir");
    UT_STR_EQUAL(sim_cli_getOutput(1), "normal");

    // Write value.
    status = sim_cli_injectInput("config maenb reset");

    // Read back.
    status = sim_cli_injectInput("config maenb");
    UT_STR_EQUAL(sim_cli_getOutput(1), "0");

    // Set to non default.
    status = sim_cli_injectInput("config osp 3.7");
    status = sim_cli_injectInput("config motdir invert");
    status = sim_cli_injectInput("config maenb 1");

    // Do the reset.
    status = sim_cli_injectInput("config all reset");

    // Test each one.
    status = sim_cli_injectInput("config egod");
    UT_STR_EQUAL(sim_cli_getOutput(1), "4.00");

    status = sim_cli_injectInput("config osp");
    UT_STR_EQUAL(sim_cli_getOutput(1), "6.00");//xxx

    status = sim_cli_injectInput("config motdir");
    UT_STR_EQUAL(sim_cli_getOutput(1), "normal");

    status = sim_cli_injectInput("config maenb");
    UT_STR_EQUAL(sim_cli_getOutput(1), "0");
}

UT_SUITE(CLI_2, "Test IO cli functions.")
{
    bool status = false;

    // Allow all commands.
    cliSetUserLevel(2);

    // Register a callback from the pushbutton module.
///    pushbuttons_regCommandCB(&commandCallback);

    // cmd > brake on
    status = sim_cli_injectInput("brake 1");
    UT_TRUE(status);
    UT_STR_EQUAL(sim_cli_getOutput(1), "OK");
    UT_TRUE(brake_getState());

    // cmd > brake off
    status = sim_cli_injectInput("brake 0");
    UT_TRUE(status);
    UT_STR_EQUAL(sim_cli_getOutput(1), "OK");
    UT_FALSE(brake_getState());

    // cmd > brake foo
    status = sim_cli_injectInput("brake foo");
    UT_TRUE(status);
    UT_STR_EQUAL(sim_cli_getOutput(1), "Invalid command");

    // cmd > clutch on
    status = sim_cli_injectInput("clutch 1");
    UT_TRUE(status);
    UT_STR_EQUAL(sim_cli_getOutput(1), "OK");
    UT_TRUE(clutch_getState());

    // cmd > clutch off
    status = sim_cli_injectInput("clutch 0");
    UT_TRUE(status);
    UT_STR_EQUAL(sim_cli_getOutput(1), "OK");
    UT_FALSE(clutch_getState());

    // cmd > clutch foo
    status = sim_cli_injectInput("clutch foo");
    UT_TRUE(status);
    UT_STR_EQUAL(sim_cli_getOutput(1), "Invalid command");

    // cmd > button
    status = sim_cli_injectInput("button");
    UT_TRUE(status);
    UT_STR_EQUAL(sim_cli_getOutput(1), "open:0 close:0 stop:0 unlock:0 motion:1");

    // cmd > button close
    status = sim_cli_injectInput("button close");
///    UT_STR_EQUAL(toString(s_lastCommand), toString(COMMAND_CLOSE));
    UT_TRUE(status);
    UT_STR_EQUAL(sim_cli_getOutput(1), "OK");

    // cmd > button foo
    status = sim_cli_injectInput("button foo");
    UT_TRUE(status);
    UT_STR_EQUAL(sim_cli_getOutput(1), "Invalid command");

    // cmd > pos
    sim_mc_setMotorPosition(53.07f);
    motioncontrol_setActualPosition(53.07f);
    status = sim_cli_injectInput("pos");
    UT_TRUE(status);
    UT_STR_EQUAL(sim_cli_getOutput(1), "Position: 1.39");
}

UT_SUITE(CLI_3, "Test cli help and password levels.")
{
    bool status = false;

    ///// Level 0 /////
    cliSetUserLevel(0);

    // Good command for this level.
    status = sim_cli_injectInput("?");
    UT_TRUE(status);
    UT_STR_EQUAL(sim_cli_getOutput(2), "'b' = 'button'");

    // Good command for this level.
    status = sim_cli_injectInput("help pwd");
    UT_TRUE(status);
    UT_STR_EQUAL(sim_cli_getOutput(2), "pwd       [password]           :Enter the password for function access");

    // Invalid command for this level.
    status = sim_cli_injectInput("clutch 0");
    UT_TRUE(status);
    UT_STR_EQUAL(sim_cli_getOutput(1), "Enter the password to access this function");

    // Bad password.
    status = sim_cli_injectInput("pwd foo");
    UT_TRUE(status);
    UT_STR_EQUAL(sim_cli_getOutput(1), "Invalid password");

    // Good password - go to level 1.
    sprintf(s_workBuff, "pwd %s", PWD_LEVEL_1);
    status = sim_cli_injectInput(s_workBuff);
    UT_TRUE(status);
    UT_STR_EQUAL(sim_cli_getOutput(1), "Level = 1");

    ///// Level 1 /////
    // Good command for this level.
    status = sim_cli_injectInput("help pwd");
    UT_TRUE(status);
    UT_STR_EQUAL(sim_cli_getOutput(2), "pwd       [password]           :Enter the password for function access");

    // Invalid command for this level.
    status = sim_cli_injectInput("help motdc");
    UT_TRUE(status);
    UT_STR_EQUAL(sim_cli_getOutput(1), "");

    // Good command for this level.
    status = sim_cli_injectInput("brake 1");
    UT_TRUE(status);
    UT_STR_EQUAL(sim_cli_getOutput(1), "OK");

    // Invalid command for this level.
    status = sim_cli_injectInput("motdc 44");
    UT_TRUE(status);
    UT_STR_EQUAL(sim_cli_getOutput(1), "Enter the password to access this function");

    // Good password - go to level 2.
    sprintf(s_workBuff, "pwd %s", PWD_LEVEL_2);
    status = sim_cli_injectInput(s_workBuff);
    UT_TRUE(status);
    UT_STR_EQUAL(sim_cli_getOutput(1), "Level = 2");

    ///// Level 2 /////
    // Good command for this level.
    status = sim_cli_injectInput("help moten");
    UT_TRUE(status);
    UT_STR_EQUAL(sim_cli_getOutput(2), "moten     [1 | 0]              :Read motor enable state, or enable/disable motor");

    // Good command for this level.
    status = sim_cli_injectInput("brake 0");
    UT_TRUE(status);
    UT_STR_EQUAL(sim_cli_getOutput(1), "OK");

    // Good command for this level.
    status = sim_cli_injectInput("moten 1");
    UT_TRUE(status);
    UT_STR_EQUAL(sim_cli_getOutput(1), "Motor state set to: enabled");

    // Good password - reset
    status = sim_cli_injectInput("pwd");
    UT_TRUE(status);
    UT_STR_EQUAL(sim_cli_getOutput(1), "Level = 0");
}

/* ======================= MODULE SIMULATION ==================================== */

//// Module is telling us something happened. Store it for inspection.
//void commandCallback(command_t command)
//{
//    s_lastCommand = command;
//}


/* ======================= SHARED VARIABLES ==================================== */

static void pushbuttonCallback(pushbutton_t, bool);
static void commandCallback(command_t);

static command_t s_lastCommand;
static pushbutton_t s_lastPushbutton;
static bool s_lastState;


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
