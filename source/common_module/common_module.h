
#ifndef COMMON_MODULE_H
#define COMMON_MODULE_H

/// @brief Interface to the common module.


#include "common_defs.h"


//---------------- Public API ----------------------//

/// Initialize the module.
/// @return Status.
status_t common_Init(void);

/// Set the log level threshhold.
/// @param level 0=off otherwise only log for <=level.
/// @return Status.
void common_SetLogLevel(int level);

/// Maybe log some information.
/// @param level See common_SetLogLevel().
/// @param format Format string followed by varargs.
void common_Log(int level, const char* format, ...);

/// Clean up module resources.
/// @return Status.
status_t common_Destroy(void);


#endif // COMMON_MODULE_H
