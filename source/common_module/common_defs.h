
#ifndef COMMON_DEFS_H
#define COMMON_DEFS_H

/// @brief General defs. Not really module specific.

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/// Defines success for a function that returns int status.
static const int STAT_PASS = 0;

/// Defines an error (memory, invalid data, etc) for a function that returns int status.
static const int STAT_ERR = -1;

/// Defines failure (expected, end of iteration, etc) for a function that returns int status.
static const int STAT_FAIL = -2;


#endif // COMMON_DEFS_H
