
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
    int status = RS_PASS;

    // Init modules.
    status = exec_Init();
    UT_EQUAL(status, RS_PASS);

    hal_mock_clearDigPins();

    // Some basic checks.
    bool value;

    // Good.
    status = io_GetDigInput(DIG_IN_SWITCH1, &value);
    UT_EQUAL(status, RS_PASS);
    UT_FALSE(value);
    // Bad.
    status = io_GetDigInput(static_cast<dig_input_t>(99), &value);
    UT_EQUAL(status, RS_ERR);

    // Good.
    UT_EQUAL(hal_mock_getDigPin(DIG_OUT_LED1), false);
    status = io_SetDigOutput(DIG_OUT_LED1, true);
    UT_EQUAL(status, RS_PASS);
    UT_EQUAL(hal_mock_getDigPin(DIG_OUT_LED1), true);
    // Bad.
    status = io_SetDigOutput(static_cast<dig_output_t>(99), true);
    UT_EQUAL(status, RS_ERR);

    // Exit.
    status = exec_Destroy();
    UT_EQUAL(status, RS_PASS);

    return 0;
}


//--------------------------------------------------------------//
UT_SUITE(CMOD_ANA_IO, "Test analog read/write.")
{
    int status = RS_PASS;

    // Init modules.
    status = exec_Init();
    UT_EQUAL(status, RS_PASS);

    // Future steps.

    // Exit.
    status = exec_Destroy();
    UT_EQUAL(status, RS_PASS);

    return 0;
}
