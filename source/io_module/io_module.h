
#ifndef IO_MODULE_H
#define IO_MODULE_H

#include "common_module.h"

/// @brief Interface to the IO module.
/// This module translates between logical and physical spaces.
/// It's not actually necessary but usually a layer like this is helpful.
/// Otherwise go straight to the hal_module.


//---------------- Public API ----------------------//

// Enums to abstract purpose from physical.
// Here the assigned values are the pin numbers but you would be more clever
// in a real application.

/// Digital inputs. 
typedef enum
{
    DIG_IN_BUTTON1 = 1,
    DIG_IN_BUTTON2 = 2,
    DIG_IN_BUTTON3 = 3,
    DIG_IN_SWITCH1 = 4,
    DIG_IN_SWITCH2 = 5,
    DIG_IN_END
} dig_input_t;

/// Digital inputs.
typedef enum
{
    DIG_OUT_LED1  = 10,
    DIG_OUT_LED2  = 11,
    DIG_OUT_RELAY = 12,
    DIG_OUT_END
} dig_output_t;

/// Digital inputs.
typedef enum
{
    ANA_IN_TEMP = 20,
    ANA_IN_VELOCITY = 21,
    ANA_IN_END
} ana_input_t;

/// Digital inputs.
typedef enum
{
    ANA_OUT_PRESSURE = 18,
    ANA_OUT_END
} ana_output_t;


// For readability.
static const bool DIG_ON = true;
static const bool DIG_OFF = false;

/// Type: Function pointer for registration of digital input changes.
/// @param which The input whose state has changed.
/// @param value The new state of the input.
typedef void (*io_DigInputCallback_t)(dig_input_t which, bool value);

/// Type: Function pointer for registration of analog input changes.
/// @param which The input whose state has changed.
/// @param value The new value of the input.
typedef void (*io_AnaInputCallback_t)(ana_input_t which, uint16_t value);

/// Initialize the module.
/// @return Status.
status_t io_Init(void);

/// Client registers a digital callback.
/// @param which Specific input number.
/// @param fp The callback function.
/// @return Status.
status_t io_RegDigInputCallback(dig_input_t which, io_DigInputCallback_t fp);

/// Set the value of a specific digital output.
/// @param which Specific output number.
/// @param value The value to set.
/// @return Status.
status_t io_SetDigOutput(dig_output_t which, bool value);

/// Get the value of a specific digital input.
/// @param which Specific input number.
/// @param value Where to put the value.
/// @return Status.
status_t io_GetDigInput(dig_input_t which, bool* value);

/// Get the value of a specific digital output.
/// @param which Specific output number.
/// @param value Where to put the value.
/// @return Status.
status_t io_GetDigOutput(dig_output_t which, bool* value);

/// Client registers an analog callback.
/// @param which Specific input number.
/// @param fp The callback function.
/// @return Status.
status_t io_RegAnaInputCallback(ana_input_t which, io_AnaInputCallback_t fp);

/// Set the value of a specific analog output.
/// @param which Specific output number.
/// @param value The value to set.
/// @return Status.
status_t io_SetAnaOutput(ana_output_t which, uint16_t value);

/// Get the value of a specific analog input.
/// @param which Specific input number.
/// @param value Where to put the value.
/// @return Status.
status_t io_GetAnaInput(ana_input_t which, uint16_t* value);

/// Clean up module resources.
/// @return Status.
status_t io_Destroy(void);


#endif // IO_MODULE_H
