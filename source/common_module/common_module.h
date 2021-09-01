
#ifndef COMMON_MODULE_H
#define COMMON_MODULE_H

/// @brief Interface to the common module.


#include "common_defs.h"


//---------------- Public API ----------------------//

/// Initialize the module.
/// @return Status.
int common_Init(void);

/// Maybe log some information.
/// @param format Format string followed by varargs.
void common_Log(const char* format, ...);

/// Clean up module resources.
/// @return Status.
int common_Destroy(void);


#endif // COMMON_MODULE_H
