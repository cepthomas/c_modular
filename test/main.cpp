
#include <iostream>
#include <fstream>

#include "pnut.h"


int main()
{
    TestManager& tm = TestManager::Instance();

    // Run the requested tests. Probably should be obtained from the command line.
    std::vector<std::string> whichSuites;
    whichSuites.push_back("XXX");
    tm.RunSuites(whichSuites, 'r');

    return 0;
}
