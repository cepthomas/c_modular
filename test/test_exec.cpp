
#include <cstdio>
#include <cstring>

#include "pnut.h"

extern "C"
{
#include "exec_module.h"
#include "io_module.h"
#include "hal_board_mock.h"
}


/// Helper macro.
#define DO_TICKS(num) for(int i = 0; i < (num); i++) { hal_mock_timerTick(); }



//--------------------------------------------------------------//
UT_SUITE(CMOD_EXEC_BASIC, "Test init/exit and common stuff.")
{
    status_t status = STATUS_OK;

    // Init modules.
    status = exec_Init();
    UT_EQUAL(status, STATUS_OK);

    // Logging.
    // Disable logging.
    common_Log("1 - This should not appear.");
    UT_STR_EQUAL(hal_mock_getLastLogWrite(), "");

    // Selective logging.
    common_Log("2 - This should appear.");
    UT_STR_EQUAL(hal_mock_getLastLogWrite(), "2 - This should appear.");
    common_Log("3 - This should not appear.");
    UT_STR_EQUAL(hal_mock_getLastLogWrite(), "2 - This should appear.");

    // Exit.
    status = exec_Destroy();
    UT_EQUAL(status, STATUS_OK);

    return 0;
}


//--------------------------------------------------------------//
UT_SUITE(CMOD_EXEC_LOOP, "Test the dynamic periodic processing.")
{
    status_t status = STATUS_OK;

    // Init modules.
    status = exec_Init();
    UT_EQUAL(status, STATUS_OK);

    // We can't actually call exec_run() without setting up some worker threads (another day)
    // so we will just pretend we are that loop.
    hal_mock_clearDigPins();

    hal_EnbInterrupts(true);
    hal_mock_setNextSerRead("SET LED1");

    DO_TICKS(49);
    UT_EQUAL(hal_mock_getDigPin(DIG_OUT_LED1), false);
    UT_EQUAL(hal_mock_getDigPin(DIG_OUT_RELAY), false);

    DO_TICKS(3);
    UT_EQUAL(hal_mock_getDigPin(DIG_OUT_LED1), true);
    UT_EQUAL(hal_mock_getDigPin(DIG_OUT_RELAY), false);

    DO_TICKS(200);
    UT_EQUAL(hal_mock_getDigPin(DIG_OUT_LED1), true);
    UT_EQUAL(hal_mock_getDigPin(DIG_OUT_RELAY), true);

    hal_EnbInterrupts(false);

    // Exit.
    status = exec_Destroy();
    UT_EQUAL(status, STATUS_OK);

    return 0;
}
