
#include "common_module.h"


//---------------- Private --------------------------//



//---------------- Public API Implementation -------------//

//--------------------------------------------------------//
status_t cli_init()
{
    status_t stat = STATUS_OK;

    return stat;
}


//--------------------------------------------------------//
status_t cli_process(const char* cmd, const char* resp) //TODO
{
    (void)cmd;
    (void)resp;

    status_t stat = STATUS_OK;

    return stat;
}


//---------------- Private --------------------------//






/* ======================= old ========================================= */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
//#include "system_defs.h"
//#include "serial_port.h"
//#include "cli_lib.h"
//#include "cli_commands.h"
//#include "cli_string.h"
//#include "debug_log.h"
//#include "configuration.h"
//#include "gitcommit.h"


//bool cliLogCmd(uint16_t argc, char* argv[], CliCommandData* pData)
//{
//    int16_t cliPort = pData->cliPort;

//    if (argc >= 2)
//    {
//        uint16_t level = toUInt16(argv[1], 0, 10);
//        if (conversionError())
//        {
//            serialWriteLine("invalid value", (uint16_t)cliPort);
//        }
//        else
//        {
//            debugLogSetLevel(level);
//        }
//    }

//    sprintf(pData->printBuf, "Log output level = %d", debugLogGetLevel());
//    serialWriteLine(pData->printBuf, (uint16_t)cliPort);

//    return true;
//}

///* -------------------------------------------------------------------------- */

//bool cliPwdCmd(uint16_t argc, char* argv[], CliCommandData* pData)
//{
//    int newLevel = -1;

//    if(argc == 2)
//    {
//        const char* cmd = argv[1];

//        if(strcmp(cmd, PWD_LEVEL_1) == 0)
//        {
//            newLevel = 1;
//        }
//        else if(strcmp(cmd, PWD_LEVEL_2) == 0)
//        {
//            newLevel = 2;
//        }
//    }
//    else
//    {
//        newLevel = 0;
//    }

//    if(newLevel == -1)
//    {
//        serialWriteLine("Invalid password", (uint16_t)pData->cliPort);
//        newLevel = 0;
//    }
//    else
//    {
//        sprintf(pData->printBuf, "Level = %d", newLevel);
//        serialWriteLine(pData->printBuf, (uint16_t)pData->cliPort);
//    }

//    // Tell configuration and cli about the change.
//    configuration_setInt(EDS_USER_LEVEL, newLevel);
//    cliSetUserLevel(newLevel);

//    return true;
//}

///* -------------------------------------------------------------------------- */

//bool cliVersionCmd(uint16_t argc, char* argv[], CliCommandData* pData)
//{
//    (void)argc;
//    (void)argv;

//    sprintf(pData->printBuf, PROGRAM_NAME);
//    serialWriteLine(pData->printBuf, (uint16_t)pData->cliPort);
//    sprintf(pData->printBuf, "Fingerprint: %s", GIT_HASH_STRING);
//    serialWriteLine(pData->printBuf, (uint16_t)pData->cliPort);

//    return true;
//}


/* --------------------------------------------------------------------------
// List of all commands supported by the CLI.
// User levels are 0-default, 1-installer 2-developer.
const CliCommandInfo sCommands[] =
{
    {"help",      cliHelpCmd,           0, 1, 2,
                  "[cmdname]", "Show command description(s)"},
    {"version",   cliVersionCmd,        0, 1, 1,
                  "", "Show firmware version and build"},
    {"pwd",       cliPwdCmd,            0, 1, 2,
                  "[password]", "Enter the password for function access"},
    {"loglevel",  cliLogCmd,            1, 1, 2,
                  "[level]", "Show or set log output level"},
    {"config",    cliConfigCmd,         1, 2, 3,
                  "(item | all | changed) [value | reset]" , "Show or set value for configuration item"},
    {"brake",     cliBrakeCmd,          1, 2, 2,
                  "(1 | 0)", "Turn brake on or off"},
    {"clutch",    cliClutchCmd,         1, 2, 2,
                  "(1 | 0)", "Turn clutch on or off"},
    {"button",    cliButtonCmd,         1, 1, 2,
                  "[open | close | stop | unlock | motion]", "Show states or simulate a button press"},
    {"pos",       cliPositionCmd,       1, 1, 1,
                  "", "Display current door position"},
    {"motdc",     cliMotorDCCmd,        2, 1, 2,
                  "[duty cycle]", "Read or set the motor duty cycle manually"},
    {"moten",     cliMotorEnCmd,        2, 1, 2,
                  "[1 | 0]", "Read motor enable state, or enable/disable motor"},
    {"kp",        cliControlkpCmd,      2, 1, 2,
                  "Kp", "Read or set proportional gain Kp"},
    {"ki",        cliControlkiCmd,      2, 1, 2,
                  "Ki", "Read or set proportional gain Ki"},
    {"cp",        cliControlcpCmd,      2, 1, 2,
                  "cp", "Read or set commanded position"},
    {"ap",        cliControlapCmd,      2, 1, 2,
                  "ap", "Read or set actual position"},
    {"cv",        cliControlcvCmd,      2, 1, 2,
                  "cv", "Read commanded velocity"},
    {"av",        cliControlavCmd,      2, 1, 2,
                  "av", "Read actual velocity"},
    {"mv",        cliControlmvCmd,      2, 1, 2,
                  "[-10, 10]", "start velocity move inches per second"},
    {"mp",        cliControlmpCmd,      2, 1, 3,
                  "[0, 500] [0, 10]", "start position move: inches inches per second"},
    {"ms",        cliControlmsCmd,      2, 1, 2,
                  "ms", "move stop"},
    {"mh",        cliControlmhCmd,      2, 1, 2,
                  "mh", "move halt"},
    {"er",        cliControlerCmd,      2, 1, 2,
                  "er", "read position error"},
    {"temp",      cliTempCmd,           1, 1, 1,
                  "", "read temperature inputs"},
    {"eraseconfig", cliConfigErase,     2, 1, 1,
                  "", "erase and reset configuration"},
    {"eraseprof", cliProfErase,         2, 1, 1,
                  "", "erase saved friction profiles"},
    {"dumpprof",  cliProfDump,         2, 1, 1,
                  "", "print live friction profile values to console"},
    {NULL,        NULL,                 0, 0, 0, NULL, NULL}
};
*/

