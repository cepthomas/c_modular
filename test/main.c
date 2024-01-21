
#include <string.h>

#include "exec_module.h"
#include "io_module.h"
#include "cli_module.h"
#include "hal_board_mock.h"


// Helper macro.
#define DO_TICKS(num) for(int i = 0; i < (num); i++) { hal_mock_timerTick(); }

// Testers.
#define UT_EQUAL(value, expected) { if((value) != (expected)) { printf("%d: [%d] should be [%d]", __LINE__, value, expected); } }
#define UT_STR_EQUAL(value, expected) { if(strcmp(value, expected) != 0) { printf("%d: [%s] should be [%s]", __LINE__, value, expected); } }
#define UT_TRUE(value) { if(!value) { printf("%d: [%d] should be true", __LINE__, value); } }
#define UT_FALSE(value) { if(value) { printf("%d: [%d] should be false", __LINE__, value); } }


int main(int argc, char* argv[])
{
    //--------------------------------------------------------------//
    // Test init/exit and common stuff.
    {
        int status = STAT_PASS;

        // Init modules.
        status = exec_Init();
        UT_EQUAL(status, STAT_PASS);

        // Logging.
        common_Log("1 - This should not appear.");
        common_Log("2 - This should appear.");
        UT_STR_EQUAL(hal_mock_getLastLogWrite(), "2 - This should appear.");

        // Exit.
        status = exec_Destroy();
        UT_EQUAL(status, STAT_PASS);
    }

    //--------------------------------------------------------------//
    // Test the dynamic periodic processing.
    {
        int status = STAT_PASS;

        // Init modules.
        status = exec_Init();
        UT_EQUAL(status, STAT_PASS);

        // We can't actually call exec_run() without setting up some worker threads (another day)
        // so we will just pretend we are that loop.
        hal_mock_clearDigPins();

        hal_EnbInterrupts(true);
        hal_mock_setNextSerRead("SET LED1");

        DO_TICKS(49);
        UT_FALSE(hal_mock_getDigPin(DIG_OUT_LED1));
        UT_FALSE(hal_mock_getDigPin(DIG_OUT_RELAY));

        DO_TICKS(3);
        UT_TRUE(hal_mock_getDigPin(DIG_OUT_LED1));
        UT_FALSE(hal_mock_getDigPin(DIG_OUT_RELAY));

        DO_TICKS(200);
        UT_TRUE(hal_mock_getDigPin(DIG_OUT_LED1));
        UT_TRUE(hal_mock_getDigPin(DIG_OUT_RELAY));

        hal_EnbInterrupts(false);

        // Exit.
        status = exec_Destroy();
        UT_EQUAL(status, STAT_PASS);
    }

    //--------------------------------------------------------------//
    // Test cli functions.
    {
        int status = STAT_PASS;

        // Init modules.
        status = exec_Init();
        UT_EQUAL(status, STAT_PASS);

        char resp[CLI_BUFF_LEN];
        resp[0] = 0;

        // Bad.
        status = cli_Process("FOO BAR", resp);
        UT_EQUAL(status, STAT_FAIL);
        UT_STR_EQUAL(resp, "NG");
        // Good.
        status = cli_Process("SET LED1", resp);
        UT_EQUAL(status, STAT_PASS);
        UT_STR_EQUAL(resp, "OK");
        UT_TRUE(hal_mock_getDigPin(DIG_OUT_LED1));
        // Good.
        status = cli_Process("CLR LED1", resp);
        UT_EQUAL(status, STAT_PASS);
        UT_STR_EQUAL(resp, "OK");

        // Exit.
        status = exec_Destroy();
        UT_EQUAL(status, STAT_PASS);
    }

    //--------------------------------------------------------------//
    // Test digital read/write.
    {
        int status = STAT_PASS;

        // Init modules.
        status = exec_Init();
        UT_EQUAL(status, STAT_PASS);

        hal_mock_clearDigPins();

        // Some basic checks.
        bool value;

        // Good.
        status = io_GetDigInput(DIG_IN_SWITCH1, &value);
        UT_EQUAL(status, STAT_PASS);
        UT_FALSE(value);
        // Bad.
        status = io_GetDigInput((dig_input_t)99, &value);
        UT_EQUAL(status, STAT_ERR);

        // Good.
        UT_EQUAL(hal_mock_getDigPin(DIG_OUT_LED1), false);
        status = io_SetDigOutput(DIG_OUT_LED1, true);
        UT_EQUAL(status, STAT_PASS);
        UT_EQUAL(hal_mock_getDigPin(DIG_OUT_LED1), true);
        // Bad.
        status = io_SetDigOutput((dig_output_t)(99), true);
        UT_EQUAL(status, STAT_ERR);

        // Exit.
        status = exec_Destroy();
        UT_EQUAL(status, STAT_PASS);
    }

    //--------------------------------------------------------------//
    // Test analog read/write.
    {
        int status = STAT_PASS;

        // Init modules.
        status = exec_Init();
        UT_EQUAL(status, STAT_PASS);

        // Future steps.

        // Exit.
        status = exec_Destroy();
        UT_EQUAL(status, STAT_PASS);
    }

    return 0;
}
