
#ifndef HAL_MODULE_H
#define HAL_MODULE_H

#include "common_module.h"

/// @file


//---------------- Public API ----------------------//

// Physical IO counts.
#define NUM_DIG_PINS 16
#define NUM_ANA_INPUTS 8
#define NUM_ANA_OUTPUTS 2


//---------------- Definitions ---------------------//

/// Type: Function pointer for registration of digital input change callbacks.
/// @param which The digital input whose state has changed.
/// @param value The new state of the input.
typedef void (*fpDigInterrupt)(unsigned int which, bool value);

/// Type: Function pointer for registration of analog input change callbacks.
/// @param which The analog input whose state has changed.
/// @param value The new value of the input.
typedef void (*fpAnaInterrupt)(unsigned int channel, uint16_t value);

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

/// Send to the log.
/// @param txt Text to log.
/// @return Status.
status_t hal_log(const char* txt);

/// Clean up module resources.
/// @return Status.
status_t hal_destroy(void);


//---------------- Digital IO Functions -----------------//

/// Register for digital input interrupt.
/// @param fp Callback function.
/// @return Status.
status_t hal_regDigInterrupt(fpDigInterrupt fp);

/// Write a digital output.
/// @param pin Specific pin number.
/// @param value Value to write.
/// @return Status.
status_t hal_writeDig(unsigned int pin, bool value);

/// Read a digital input or output.
/// @param pin Specific pin number.
/// @param value Where to place the value.
/// @return Status.
status_t hal_readDig(unsigned int pin, bool* value);


//---------------- Analog IO Functions -----------------//

/// Register for analog interrupt.
/// @param fp Callback function.
/// @return Status.
status_t hal_regAnaInterrupt(fpAnaInterrupt fp);

/// Write an analog output.
/// @param pin Specific pin number.
/// @param value Value to write.
/// @return Status.
status_t hal_writeAna(unsigned int channel, uint16_t value);

/// Read an analog input.
/// @param pin Specific pin number.
/// @param value Where to place the value.
/// @return Status.
status_t hal_readAna(unsigned int channel, uint16_t* value);


//---------------- Serial Functions -----------------//

/// Open a serial port.
/// @param channel Specific channel.
/// @return Status.
status_t hal_serOpen(unsigned int channel);

/// Read from a serial channel.
/// @param channel Specific channel.
/// @param buff Data buffer. Will be a zero-terminated string.
/// @param num Length of buff.
/// @return Status.
status_t hal_serReadLine(unsigned int channel, char* buff, int num);

/// Write to a serial channel.
/// @param channel Specific channel.
/// @param buff What to send as a zero-terminated string.
/// @return Status.
status_t hal_serWriteLine(unsigned int channel, char* buff);


//---------------- Timer Functions -----------------//

/// Timer interrupts.
/// @param period How oftern in msec.
/// @param fp Callback function.
/// @return Status.
status_t hal_regTimerInterrupt(unsigned int period, fpTimerInterrupt fp);

/// Get number of microseconds since beginning.
/// @return Microseconds.
uint64_t hal_getCurrentUsec(void);

#endif // HAL_MODULE_H
