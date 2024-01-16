
#include <string.h>

#include "common_module.h"
#include "io_module.h"
#include "exec_module.h"
#include "cli_module.h"


// A very crude cli processor. Yours would be much more elegant.


//---------------- Private Declarations ------------------//

static dig_output_t p_ParseDigOutput(const char* dout)
{
    dig_output_t ret = DIG_OUT_END;

    if((strcmp("LED1", dout) == 0))
    {
        ret = DIG_OUT_LED1;
    }
    else if((strcmp("LED2", dout) == 0))
    {
        ret = DIG_OUT_LED2;
    }
    else if((strcmp("RELAY", dout) == 0))
    {
        ret = DIG_OUT_RELAY;
    }

    return ret;
}


//---------------- Public API Implementation -------------//

//--------------------------------------------------------//
int cli_Init()
{
    int stat = STAT_PASS;

    return stat;
}

//--------------------------------------------------------//
int cli_Process(const char* cmd, char* resp)
{
    (void)cmd;
    (void)resp;

    int stat = STAT_PASS;

    if(strlen(cmd) > 0)
    {
        // Split by spaces.
        const int MAX_ARGS = 4;

        // What are the options.
        char* args[MAX_ARGS];
        memset(args, 0x00, sizeof(args));
        int argind = 0;

        // Make writable copy and tokenize it.
        char cp[CLI_BUFF_LEN];
        strcpy(cp, cmd);
        char* token = strtok(cp, " ");

        while(token != NULL && argind < MAX_ARGS)
        {
            args[argind++] = token;
            token = strtok(NULL, " ");
        }

        // Determine action.
        if((strcmp("EXIT", args[0]) == 0))
        {
            exec_Destroy();
        }
        else if((strcmp("SET", args[0]) == 0))
        {
            dig_output_t dout = p_ParseDigOutput(args[1]);
            stat = io_SetDigOutput(dout, true);
        }
        else if((strcmp("CLR", args[0]) == 0))
        {
            dig_output_t dout = p_ParseDigOutput(args[1]);
            stat = io_SetDigOutput(dout, false);
        }
        else
        {
            stat = STAT_FAIL;
        }

        strcpy(resp, stat == STAT_PASS ? "OK" : "NG");
    }

    return stat;
}

//--------------------------------------------------------//
int cli_Destroy(void)
{
    int stat = STAT_PASS;

    return stat;
}

//---------------- Private Implementation ----------------//

