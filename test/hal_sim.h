
#ifndef HAL_SIM_H
#define HAL_SIM_H

#include "hal_module.h"


//---------------- Simulator Support ---------------------//

/// Tickle an input pin.
/// @param pin Specific pin number.
/// @param state What to set it to.
void hal_sim_injectDigInput(unsigned int pin, bool state);

/// Clear all pin states.
void hal_sim_clearDigPins();

/// Get a cached pin state.
/// @param pin Specific pin number.
/// @return The value.
bool hal_sim_getDigPin(unsigned int pin);

/// Get the most recent serial port write.
/// @return The text sent.
const char* hal_sim_getLastSerWrite();

/// Get the most recent log write.
/// @return The text logged.
const char* hal_sim_getLastLogWrite();

/// Preload the next simulated serial read.
/// @param s The text.
void hal_sim_setNextSerRead(const char* s);

/// Do a system timer tick.
void hal_sim_timerTick();

#endif // HAL_SIM_H
