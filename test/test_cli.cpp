
#include <stdio.h>
#include <string.h>

#include "pnut.h"

extern "C"
{
 #include "exec_module.h"
// #include "common_module.h"
// #include "hal_module.h"
// #include "io_module.h"
#include "cli_module.h"
#include "hal_sim.h"
}


//--------------------------------------------------------------//
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
