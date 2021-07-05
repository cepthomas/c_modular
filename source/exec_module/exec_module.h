

#ifndef EXEC_MODULE_H
#define EXEC_MODULE_H

#include "common_module.h"


/// @brief Interface to the exec module.


//---------------- Public API ----------------------//

/// Initialize the module.
/// @return Status.
status_t exec_Init(void);

/// Enter the forever loop.
/// @return Status on exit.
status_t exec_Run(void);

/// Stop and clean up module resources.
/// @return Status.
status_t exec_Destroy(void);


#endif // EXEC_MODULE_H
