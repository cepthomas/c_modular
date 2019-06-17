
#include <iostream>
#include <fstream>

#include "pnut.h"

// Entry point for the tester.

int main()
{
    TestManager& tm = TestManager::Instance();

    // Run the requested tests. Probably should be obtained from the command line.
    std::vector<std::string> whichSuites;
    whichSuites.emplace_back("CMOD");
    tm.RunSuites(whichSuites, 'r');

    printf("Don't forget to run_mem_chk!\n");

    return 0;
}
