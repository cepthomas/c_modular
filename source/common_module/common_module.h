
#ifndef COMMON_MODULE_H
#define COMMON_MODULE_H

/// @file


#include "common_defs.h"


//---------------- Public API ----------------------//


//---------------- Definitions ---------------------//


//---------------- Functions ---------------------//

/// Initialize the module.
/// @return Status.
status_t common_init(void);

/// Get microseconds since boot time.
/// @return The usecs.
uint64_t common_getUsec(void);

/// Set the log level threshhold.
/// @param level 0=off otherwise only log for <=level.
/// @return Status.
void common_setLogLevel(int level);

/// Maybe log some information. Does not add newline - up to client.
/// @param level See common_setLogLevel().
/// @param format Format string followed by varargs.
void common_debugLog(int level, const char* format, ...);

#endif // COMMON_MODULE_H
