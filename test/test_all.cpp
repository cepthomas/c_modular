
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
#include "hal_sim.h"
}



UT_SUITE(CMOD_BASIC, "Test init/exit and common stuff.")
{
    status_t status = STATUS_OK;

    // Init modules.
    status = exec_init();
    UT_EQUAL(status, STATUS_OK);

    // Logging.
    // Disable logging.
    common_setLogLevel(0);
    common_log(3, "1 - This should not appear.");
    UT_STR_EQUAL(sim_getLastLogWrite(), "");

    // Selective logging.
    common_setLogLevel(2);
    common_log(2, "2 - This should appear.");
    UT_STR_EQUAL(sim_getLastLogWrite(), "2 - This should appear.");
    common_log(3, "3 - This should not appear.");
    UT_STR_EQUAL(sim_getLastLogWrite(), "2 - This should appear.");

    // Exit.
    status = exec_exit();
    UT_EQUAL(status, STATUS_OK);
}

UT_SUITE(CMOD_DIGIO, "Test digital read/write.")
{
    status_t status = STATUS_OK;

    // Init modules.
    status = exec_init();
    UT_EQUAL(status, STATUS_OK);

    // Some basic checks.
    bool value;

    // Good.
    status = io_getDigInput(DIG_IN_SWITCH1, &value);
    UT_EQUAL(status, STATUS_OK);
    UT_FALSE(value);
    // Bad.
    status = io_getDigInput((digInput_t)99, &value);
    UT_EQUAL(status, STATUS_ERROR);

    // Good.
        
    UT_EQUAL(sim_io_getOutputPin(DIG_OUT_LED1), false);
    status = io_setDigOutput(DIG_OUT_LED1, true);
    UT_EQUAL(status, STATUS_OK);
    UT_EQUAL(sim_io_getOutputPin(DIG_OUT_LED1), true);
    // Bad.
    status = io_setDigOutput((digOutput_t)99, true);
    UT_EQUAL(status, STATUS_ERROR);

    // Exit.
    status = exec_exit();
    UT_EQUAL(status, STATUS_OK);
}


UT_SUITE(CMOD_PUMP, "Test the periodic processing.")
{
    status_t status = STATUS_OK;

    // Init modules.
    status = exec_init();
    UT_EQUAL(status, STATUS_OK);


    /////////// stuff here ///////////////


    // Exit.
    status = exec_exit();
    UT_EQUAL(status, STATUS_OK);
}


UT_SUITE(CMOD_CLI, "Test cli functions.")
{
    status_t status = STATUS_OK;

    // Init modules.
    status = exec_init();
    UT_EQUAL(status, STATUS_OK);


    /////////// stuff here ///////////////


    // Exit.
    status = exec_exit();
    UT_EQUAL(status, STATUS_OK);
}
