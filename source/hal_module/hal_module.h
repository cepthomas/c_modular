
#ifndef HAL_MODULE_H
#define HAL_MODULE_H

#include "common_module.h"

/// @file


//---------------- Public API ----------------------//

// Physical pin counts.
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

/// Turn interrupts on/off.
/// @param env On/off.
/// @return Status.
status_t hal_enbInterrupts(bool enb);

/// Run the hardware loop.
/// @return Status.
status_t hal_pump(void);

/// Send to the log.
/// @param txt Text to log.
/// @return Status.
status_t hal_log(const char* txt);


//---------------- Digital IO Functions -----------------//

/// Register for digital input interrupt.
/// @param fp Callback function.
/// @return Status.
status_t hal_regDigInterrupt(fpDigInterrupt fp);

/// Write a digital output.
/// @param pin Specific pin number.
/// @param value Value to write.
/// @return Status.
status_t hal_writePin(int pin, bool value);

/// Read a digital input.
/// @param pin Specific pin number.
/// @param value Where to place the value.
/// @return Status.
status_t hal_readPin(int pin, bool* value);


//---------------- Analog IO Functions -----------------//

/// Register for analog interrupt.
/// @param fp Callback function.
/// @return Status.
status_t hal_regAnaInterrupt(fpAnaInterrupt fp);

/// Write an analog output.
/// @param pin Specific pin number.
/// @param value Value to write.
/// @return Status.
status_t hal_writeAna(int channel, uint16_t value);

/// Read an analog input.
/// @param pin Specific pin number.
/// @param value Where to place the value.
/// @return Status.
status_t hal_readAna(int channel, uint16_t* value);


//---------------- Serial Functions -----------------//

/// Open a serial port.
/// @param channel Specific channel.
/// @return Status.
status_t hal_serOpen(int channel);

/// Read from a serial channel. TODO block?
/// @param channel Specific channel.
/// @param buff Data buffer. Will be a zero-terminated string.
/// @param num Length of buff.
/// @return Status.
status_t hal_serReadLine(int channel, char* buff, int num);

/// Write to a serial channel.
/// @param channel Specific channel.
/// @param buff What to send as a zero-terminated string.
/// @return Status.
status_t hal_serWriteLine(int channel, char* buff);


//---------------- Timer Functions -----------------//

/// Timer interrupts.
/// @param period How oftern in msec.
/// @param fp Callback function.
/// @return Status.
status_t hal_regTimerInterrupt(int period, fpTimerInterrupt fp);

/// Get number of microseconds since beginning.
/// @return Microseconds.
uint64_t hal_getCurrentUsec(void);

#endif // HAL_MODULE_H
