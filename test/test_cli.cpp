
#include <stdio.h>
#include <string.h>

#include "pnut.h"

extern "C"
{
#include "exec_module.h"
#include "cli_module.h"
#include "io_module.h"
#include "hal_board_mock.h"
}


//--------------------------------------------------------------//
UT_SUITE(CMOD_CLI, "Test cli functions.")
{
    int status = RS_PASS;

    // Init modules.
    status = exec_Init();
    UT_EQUAL(status, RS_PASS);

    char resp[CLI_BUFF_LEN];
    resp[0] = 0;

    // Bad.
    status = cli_Process("FOO BAR", resp);
    UT_EQUAL(status, RS_FAIL);
    UT_STR_EQUAL(resp, "NG");
    // Good.
    status = cli_Process("SET LED1", resp);
    UT_EQUAL(status, RS_PASS);
    UT_STR_EQUAL(resp, "OK");
    UT_TRUE(hal_mock_getDigPin(DIG_OUT_LED1));
    // Good.
    status = cli_Process("CLR LED1", resp);
    UT_EQUAL(status, RS_PASS);
    UT_STR_EQUAL(resp, "OK");

    // Exit.
    status = exec_Destroy();
    UT_EQUAL(status, RS_PASS);

    return 0;
}
