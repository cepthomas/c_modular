
#include <string.h>

#include "common_module.h"
#include "io_module.h"
#include "exec_module.h"
#include "cli_module.h"


// A very crude cli processor. Yours would be much more elegant.


//---------------- Private --------------------------//

static digOutput_t p_parseDigOutput(const char* dout)
{
    digOutput_t ret = DIG_OUT_END;

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
status_t cli_init()
{
    status_t stat = STATUS_OK;

    return stat;
}

//--------------------------------------------------------//
status_t cli_process(const char* cmd, char* resp)
{
    (void)cmd;
    (void)resp;

    status_t stat = STATUS_OK;

    if(strlen(cmd) > 0)
    {
        // Split by spaces.
        #define MAX_ARGS 4

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
            exec_exit();
        }
        else if((strcmp("SET", args[0]) == 0))
        {
            digOutput_t dout = p_parseDigOutput(args[1]);
            stat = io_setDigOutput(dout, true);
        }
        else if((strcmp("CLR", args[0]) == 0))
        {
            digOutput_t dout = p_parseDigOutput(args[1]);
            stat = io_setDigOutput(dout, false);
        }
        else
        {
            stat = STATUS_WARN;
        }

        strcpy(resp, stat == STATUS_OK ? "OK" : "NG");
    }

    return stat;
}


//---------------- Private --------------------------//

