
#ifndef HAL_SIM_H
#define HAL_SIM_H


//---------------- Simulator API functions ----------------------//

/// Tickle an input pin.
/// @param pin
/// @param state
void sim_io_injectInput(int pin, bool state);

/// Clear all simulated interrupts.
void sim_io_clearInterrupts();

/// Clear all simulated pin states.
void sim_io_clearInputs();

/// Clear all cached pin states.
void sim_io_clearOutputs();

/// Get a cached pin state.
/// @param pin
/// @return
bool sim_io_getOutputPin(int pin);

/// Simulated user input from cli.
/// @param input
/// @return
bool sim_cli_InjectInput(const char* input);

/// Get whatever cli module returned to the user.
/// @param which
/// @return
const char* sim_cli_GetOutput(int which);


#endif // HAL_SIM_H
