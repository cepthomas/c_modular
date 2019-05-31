
#ifndef HAL_MODULE_H
#define HAL_MODULE_H

#include "common_module.h"

/// @file


//---------------- Public API ----------------------//

//---------------- Definitions ---------------------//

// // How many of each.
// #define NUM_DIG_IN     8
// #define NUM_DIG_OUT    8
// #define NUM_ANA_IN     4
// #define NUM_ANA_OUT    2
// #define SER_BUFF_LEN  64


/// Type: Function pointer for registration of digital input change callbacks.
/// @param which The digital input whose state has changed.
/// @param value The new state of the input.
typedef void (*fpDigInterrupt)(int which, bool value);

/// Type: Function pointer for registration of analog input change callbacks.
/// @param which The analog input whose state has changed.
/// @param value The new value of the input.
typedef void (*fpAnaInterrupt)(int channel, uint16_t value);

/// Type: Function pointer for handling of timer ticks.
typedef void (*fpTimerInterrupt)(void);


//---------------- General Functions -----------------//

/// Initialize the module.
/// @return Status.
status_t hal_init(void);

/// Mod_desc.
/// @param name desc.
/// @return Status.
status_t hal_enbInterrupts(bool);

//---------------- Digital Functions -----------------//

// Digital I/O
/// Mod_desc.
/// @param name desc.
/// @return Status.
status_t hal_regDigInterrupt(fpDigInterrupt fp);

/// Mod_desc.
/// @param name desc.
/// @return Status.
status_t hal_writePin(int pin, bool value);

/// Mod_desc.
/// @param name desc.
/// @return Status.
status_t hal_readPin(int pin, bool* value);


//---------------- Analog Functions -----------------//

// Analog I/O
/// Mod_desc.
/// @param name desc.
/// @return Status.
status_t hal_regAnaInterrupt(fpAnaInterrupt fp);

/// Mod_desc.
/// @param name desc.
/// @return Status.
status_t hal_writeAna(int channel, uint16_t value);

/// Mod_desc.
/// @param name desc.
/// @return Status.
status_t hal_readAna(int channel, uint16_t* value);


//---------------- Serial Functions -----------------//

// Serial I/O
/// Mod_desc.
/// @param name desc.
/// @return Status.
status_t hal_openSer(int channel);

/// Mod_desc.
/// @param name desc.
/// @return Status.
status_t hal_readSer(int channel, char* buff, int* num);

/// Mod_desc.
/// @param name desc.
/// @return Status.
status_t hal_writeSer(int channel, char* buff, int* num);


//---------------- Timer Functions -----------------//

// Timers
/// Mod_desc.
/// @param name desc.
/// @return Status.
status_t hal_regTimerInterrupt(int when, fpTimerInterrupt fp);


#endif // HAL_MODULE_H
