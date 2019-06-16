
#ifndef COMMON_DEFS_H
#define COMMON_DEFS_H

/// @file General defs. Not really module specific.

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


/// General status value.
typedef enum
{
    STATUS_OK = 0,
    STATUS_WARN,
    STATUS_ERROR,
    STATUS_FATAL
} status_t;

#endif // COMMON_DEFS_H
