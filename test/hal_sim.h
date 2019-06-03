
#ifndef HAL_SIM_H
#define HAL_SIM_H

#include "hal_module.h"


//---------------- Simulator Support ---------------------//

/// Tickle an input pin.
/// @param pin Specific pin number.
/// @param state What to set it to.
void hal_sim_injectInput(int pin, bool state);

/// Clear all simulated interrupts.
void hal_sim_clearInterrupts();

/// Clear all simulated pin states.
void hal_sim_clearInputs();

/// Clear all cached pin states.
void hal_sim_clearOutputs();

/// Get a cached pin state.
/// @param pin Specific pin number.
/// @return The value.
bool hal_sim_getOutputPin(int pin);

/// Get the most recent serial port write.
/// @return The text sent.
const char* hal_sim_getLastSerWrite();

/// Get the most recent log write.
/// @return The text logged.
const char* hal_sim_getLastLogWrite();

/// Preload the next simulated serial read.
/// @param pin The text.
void hal_sim_setNextSerRead(const char* s);

#endif // HAL_SIM_H
