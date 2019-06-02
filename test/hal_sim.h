
#ifndef HAL_SIM_H
#define HAL_SIM_H


//---------------- Simulator API functions ----------------------//

/// Tickle an input pin.
/// @param pin Specific pin number.
/// @param state What to set it to.
void sim_io_injectInput(int pin, bool state);

/// Clear all simulated interrupts.
void sim_io_clearInterrupts();

/// Clear all simulated pin states.
void sim_io_clearInputs();

/// Clear all cached pin states.
void sim_io_clearOutputs();

/// Get a cached pin state.
/// @param pin Specific pin number.
/// @return The value.
bool sim_io_getOutputPin(int pin);

/// Get the most recent serial port write.
/// @return The text sent.
const char* sim_getLastSerWrite();

/// Get the most recent log write.
/// @return The text logged.
const char* sim_getLastLogWrite();

/// Preload the next simulated serial read.
/// @param pin The text.
void sim_setNextSerRead(const char* s);

#endif // HAL_SIM_H
