
#ifndef IO_MODULE_H
#define IO_MODULE_H

#include "common_module.h"

/// @file

// This module translates between logical and physical spaces.
// It's not actually necessary but usually a layer like this is helpful.
// Otherwise go straight to the hal_module.


//---------------- Public API ----------------------//


//---------------- Definitions ---------------------//

typedef enum
{
    DIG_IN_BUTTON1,
    DIG_IN_BUTTON2,
    DIG_IN_BUTTON3,
    DIG_IN_SWITCH1,
    DIG_IN_SWITCH2,
    DIG_IN_END
} digInput_t;

typedef enum
{
    DIG_OUT_LED1,
    DIG_OUT_LED2,
    DIG_OUT_RELAY,
    DIG_OUT_END
} digOutput_t;

typedef enum
{
    ANA_IN_TEMP,
    ANA_IN_VELOCITY,
    ANA_IN_END
} anaInput_t;

typedef enum
{
    ANA_OUT_PRESSURE,
    ANA_OUT_END
} anaOutput_t;


// Helpers
#define DIG_ON true
#define DIG_OFF false


//---------------- Functions ---------------------//

/// Type: Function pointer for registration of digital input changes.
/// @param which The input whose state has changed.
/// @param value The new state of the input.
typedef void (*fpDigInputCallback)(digInput_t which, bool value);

/// Type: Function pointer for registration of analog input changes.
/// @param which The input whose state has changed.
/// @param value The new value of the input.
typedef void (*fpAnaInputCallback)(anaInput_t which, uint16_t value);


/// Initialize the module.
/// @return Status.
status_t io_init(void);

/// Client registers a digital callback.
/// @param which Specific input number.
/// @param fp The callback function.
/// @return Status.
status_t io_regDigInputCallback(digInput_t which, fpDigInputCallback fp);

/// Set the value of a specific digital output.
/// @param which Specific output number.
/// @param value The value to set.
/// @return Status.
status_t io_setDigOutput(digOutput_t which, bool value);

/// Get the value of a specific digital input.
/// @param which Specific input number.
/// @param value Where to put the value.
/// @return Status.
status_t io_getDigInput(digInput_t which, bool* value);

/// Client registers an analog callback.
/// @param which Specific input number.
/// @param fp The callback function.
/// @return Status.
status_t io_regAnaInputCallback(anaInput_t which, fpAnaInputCallback fp);

/// Set the value of a specific analog output.
/// @param which Specific output number.
/// @param value The value to set.
/// @return Status.
status_t io_setAnaOutput(anaOutput_t which, uint16_t value);

/// Get the value of a specific analog input.
/// @param which Specific input number.
/// @param value Where to put the value.
/// @return Status.
status_t io_getAnaInput(anaInput_t which, uint16_t* value);


#endif // IO_MODULE_H
