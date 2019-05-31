
#ifndef HAL_SIM_H
#define HAL_SIM_H





#ifdef _TO_PROCESS


/* ======================= SIMULATOR API FUNCTIONS ================== */

// Tickle a simulated IO pin.
void sim_gpio_injectInput(gpioInputPin_t pin, gpioPinState_t state);

// Clear all simulated interrupts.
void sim_gpio_clearInterrupts();

// Clear all simulated pin states.
void sim_gpio_clearInputs();

// Clear all cached pin states.
void sim_gpio_clearOutputs();

// Get a cached pin state.
bool getGpioOutputPin(gpioOutputPin_t pin);




/* ======================= SIMULATOR API FUNCTIONS ================== */

// Simulated user input from cli.
bool sim_cli_injectInput(const char* input);

// Get whatever cli module returned to the user.
const char* sim_cli_getOutput(int which);

#endif // _TO_PROCESS




#endif // HAL_SIM_H
