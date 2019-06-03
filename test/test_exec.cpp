
#include <stdio.h>
#include <string.h>

#include "pnut.h"

extern "C"
{
#include "exec_module.h"
// #include "common_module.h"
// #include "hal_module.h"
// #include "io_module.h"
// #include "cli_module.h"
#include "hal_sim.h"
}



//--------------------------------------------------------------//
UT_SUITE(CMOD_EXEC_BASIC, "Test init/exit and common stuff.")
{
    status_t status = STATUS_OK;

    // Init modules.
    status = exec_init();
    UT_EQUAL(status, STATUS_OK);

    // Logging.
    // Disable logging.
    common_setLogLevel(0);
    common_log(3, "1 - This should not appear.");
    UT_STR_EQUAL(hal_sim_getLastLogWrite(), "");

    // Selective logging.
    common_setLogLevel(2);
    common_log(2, "2 - This should appear.");
    UT_STR_EQUAL(hal_sim_getLastLogWrite(), "2 - This should appear.");
    common_log(3, "3 - This should not appear.");
    UT_STR_EQUAL(hal_sim_getLastLogWrite(), "2 - This should appear.");

    // Exit.
    status = exec_exit();
    UT_EQUAL(status, STATUS_OK);
}


//--------------------------------------------------------------//
UT_SUITE(CMOD_EXEC_LOOP, "Test the periodic processing.")
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

