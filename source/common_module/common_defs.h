
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


/// Macro to minimize boilerplate.
#define CHECKED_FUNC(_stat, _func, ...) \
{ \
    _stat = _func(__VA_ARGS__); \
    if(_stat != STATUS_OK) \
    { \
        common_log(0, "%s(%d) %s", __FILE__, __LINE__, #_func); \
    } \
}

#endif // COMMON_DEFS_H
