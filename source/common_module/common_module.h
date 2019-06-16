
#ifndef COMMON_MODULE_H
#define COMMON_MODULE_H

/// @file Interface to the common module.


#include "common_defs.h"


//---------------- Public API ----------------------//


//---------------- Definitions ---------------------//


//---------------- Functions ---------------------//

/// Initialize the module.
/// @return Status.
status_t common_init(void);

/// Set the log level threshhold.
/// @param level 0=off otherwise only log for <=level.
/// @return Status.
void common_setLogLevel(int level);

/// Maybe log some information.
/// @param level See common_setLogLevel().
/// @param format Format string followed by varargs.
void common_log(int level, const char* format, ...);

/// Clean up module resources.
/// @return Status.
status_t common_destroy(void);


#endif // COMMON_MODULE_H
