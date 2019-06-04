
#ifndef COMMON_DEFS_H
#define COMMON_DEFS_H

/// @file

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// Not really module specific.

/// General status value.
typedef enum
{
    STATUS_OK = 0,
    STATUS_WARN,
    STATUS_ERROR,
    STATUS_FATAL
} status_t;

#endif // COMMON_DEFS_H
