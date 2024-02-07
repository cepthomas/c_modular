
#include "exec_module.h"


/// Main entry for the real application. This would be called from the reset handler.
/// Process args and start system.
/// @param argc How many args.
/// @param argv The args.
/// @return Standard exit code.
int run(int argc, char* argv[])
{
    (void)argv;

    int ret = 0;

    // Get the args.
    bool showUsage = false;

    for(int i = 1; i < argc; i++)
    {
        // Process options using getopt or similar.
        //const char* carg = argv[i];
    }

    if(showUsage)
    {
        // Command line arguments were no good, print a usage message and exit.
        printf("c_modular demo [opts] filename\n");
        printf("   -x: do something\n");
        printf("   filename: the filename or uri\n");
        ret = 1;
    }
    else
    {
        if(exec_Init() == STAT_PASS)
        {
            // Blocks forever.
            ret = exec_Run();

            // Clean up.
            exec_Destroy();
            //ret = exec_destroy(;

        }
        else
        {
            ret = STAT_FAIL;
        }
    }

    return ret;
}
