
#include "exec_module.h"


/// Main entry. Process args and start system.
/// @param argc How many args
/// @param argv The args
/// @return Exit code
int main(int argc, char* argv[])
{
    (void)argv;

    int ret = 0;

    // Get the args.
    bool showUsage = false;

    for(int i = 1; i < argc; i++)
    {
        // Do options...
        //const char* carg = argv[i];
    }

    if (showUsage)
    {
        // Command line arguments were no good, print a usage message and exit.
        printf("appname [opts] filename\n");
        printf("   -x: do something\n");
        printf("   filename: the filename or uri\n");
        ret = 1;
    }
    else
    {
        if(exec_init() == STATUS_OK)
        {
            // Blocks forever.
            if(exec_run() != STATUS_OK)
            {
                ret = 3;
            }
        }
        else
        {
            ret = 2;
        }
    }

    return ret;
}
