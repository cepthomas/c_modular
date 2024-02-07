
#ifndef HAL_MOCK_H
#define HAL_MOCK_H

#include "hal_module.h"


//---------------- Mock Support ---------------------//

/// Tickle an input pin.
/// @param pin Specific pin number.
/// @param state What to set it to.
void hal_mock_injectDigInput(unsigned int pin, bool state);

/// Clear all pin states.
void hal_mock_clearDigPins();

/// Get a cached pin state.
/// @param pin Specific pin number.
/// @return The value.
bool hal_mock_getDigPin(unsigned int pin);

/// Get the most recent serial port write.
/// @return The text sent.
const char* hal_mock_getLastSerWrite();

/// Get the most recent log write.
/// @return The text logged.
const char* hal_mock_getLastLogWrite();

/// Preload the next simulated serial read.
/// @param s The text.
void hal_mock_setNextSerRead(const char* s);

/// Do a system timer tick.
void hal_mock_timerTick();

#endif // HAL_MOCK_H
