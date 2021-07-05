
#include <cstdio>
#include <cstring>

#include "pnut.h"

extern "C"
{
#include "exec_module.h"
#include "io_module.h"
#include "hal_board_mock.h"
}



//--------------------------------------------------------------//
UT_SUITE(CMOD_DIG_IO, "Test digital read/write.")
{
    status_t status = STATUS_OK;

    // Init modules.
    status = exec_init();
    UT_EQUAL(status, STATUS_OK);

    hal_mock_clearDigPins();

    // Some basic checks.
    bool value;

    // Good.
    status = io_getDigInput(DIG_IN_SWITCH1, &value);
    UT_EQUAL(status, STATUS_OK);
    UT_FALSE(value);
    // Bad.
    status = io_getDigInput(static_cast<digInput_t>(99), &value);
    UT_EQUAL(status, STATUS_ERROR);

    // Good.
    UT_EQUAL(hal_mock_getDigPin(DIG_OUT_LED1), false);
    status = io_setDigOutput(DIG_OUT_LED1, true);
    UT_EQUAL(status, STATUS_OK);
    UT_EQUAL(hal_mock_getDigPin(DIG_OUT_LED1), true);
    // Bad.
    status = io_setDigOutput(static_cast<digOutput_t>(99), true);
    UT_EQUAL(status, STATUS_ERROR);

    // Exit.
    status = exec_destroy();
    UT_EQUAL(status, STATUS_OK);

    return 0;
}


//--------------------------------------------------------------//
UT_SUITE(CMOD_ANA_IO, "Test analog read/write.")
{
    status_t status = STATUS_OK;

    // Init modules.
    status = exec_init();
    UT_EQUAL(status, STATUS_OK);

    // Future steps.

    // Exit.
    status = exec_destroy();
    UT_EQUAL(status, STATUS_OK);

    return 0;
}
