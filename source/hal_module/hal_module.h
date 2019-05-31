
#ifndef HAL_MODULE_H
#define HAL_MODULE_H

#include "common_module.h"

/// @file


//---------------- Public API ----------------------//

#define NUM_DIG_INPUTS 16
#define NUM_DIG_OUTPUTS 16
#define NUM_ANA_INPUTS 8
#define NUM_ANA_OUTPUTS 2


//---------------- Definitions ---------------------//

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

//---------------- Digital IO Functions -----------------//

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


//---------------- Analog IO Functions -----------------//

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

/// Timer interrupts.
/// @param period How oftern in msec.
/// @param fp Callback function.
/// @return Status.
status_t hal_regTimerInterrupt(int period, fpTimerInterrupt fp);

/// Get number of microseconds since reset.
/// @return Microseconds.
uint64_t hal_getPerfCtr(void);

/// Reset counter.
/// @return Microseconds.
void hal_resetPerfCtr(void);


#endif // HAL_MODULE_H
