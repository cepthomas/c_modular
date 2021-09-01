
#ifndef COMMON_DEFS_H
#define COMMON_DEFS_H

/// @brief General defs. Not really module specific.

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


/// Defines an error (allocation, iniitialization, etc) for a function that returns a pointer.
#define BAD_PTR NULL

/// Defines success for a function that returns int status.
static const int RS_PASS = 0;

/// Defines an error (memory, invalid data, etc) for a function that returns int status.
static const int RS_ERR = -1;

/// Defines failure (expected, end of iteration, etc) for a function that returns int status.
static const int RS_FAIL = -2;

/// Validate pointer arg. If fails, early returns err.
/// @param ptr Pointer.
/// @param err Error value to return in case of failure.
#define VAL_PTR(ptr, err) if(ptr == NULL) { return err; }


#endif // COMMON_DEFS_H
