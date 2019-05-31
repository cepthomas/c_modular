
#ifndef COMMON_DEFS_H
#define COMMON_DEFS_H

/// @file

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


// //TODO these macros?
// #define STD_FUNC status_t stat = STATUS_OK;
// #define STD_RET return stat;
// #define CHK_BOUNDS(what, min, max) if(what < min || what > max) stat = STATUS_INVALID_ARG;
// // #define _RS if(RET_STAT_PASS(RetStat)) RetStat = 
// // #define _RC if(RET_STAT_PASS(RetStat))  
// // #define _RF if(RET_STAT_FAIL(RetStat))  


#endif // COMMON_DEFS_H
