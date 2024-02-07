
#ifndef HAL_MODULE_H
#define HAL_MODULE_H

#include "common_module.h"

/// @brief Interface to the HAL module.


//---------------- Public API ----------------------//

// Physical IO counts.
#define NUM_DIG_PINS 16
#define NUM_ANA_INPUTS 8
#define NUM_ANA_OUTPUTS 2

/// Type: Function pointer for registration of digital input change callbacks.
/// @param which The digital input whose state has changed.
/// @param value The new state of the input.
typedef void (*hal_DigInterrupt_t)(unsigned int which, bool value);

/// Type: Function pointer for registration of analog input change callbacks.
/// @param which The analog input whose state has changed.
/// @param value The new value of the input.
typedef void (*hal_AnaInterrupt_t)(unsigned int channel, uint16_t value);

/// Type: Function pointer for handling of timer ticks.
typedef void (*hal_TimerInterrupt_t)(void);


/// Initialize the module.
/// @return Status.
int hal_Init(void);

/// Turn interrupts on/off.
/// @param env On/off.
/// @return Status.
int hal_EnbInterrupts(bool enb);

/// Send to the log.
/// @param txt Text to log.
/// @return Status.
int hal_Log(const char* txt);

/// Clean up module resources.
/// @return Status.
int hal_Destroy(void);


//---------------- Digital IO Functions -----------------//

/// Register for digital input interrupt.
/// @param fp Callback function.
/// @return Status.
int hal_RegDigInterrupt(hal_DigInterrupt_t fp);

/// Write a digital output.
/// @param pin Specific pin number.
/// @param value Value to write.
/// @return Status.
int hal_WriteDig(unsigned int pin, bool value);

/// Read a digital input or output.
/// @param pin Specific pin number.
/// @param value Where to place the value.
/// @return Status.
int hal_ReadDig(unsigned int pin, bool* value);


//---------------- Analog IO Functions -----------------//

/// Register for analog interrupt.
/// @param fp Callback function.
/// @return Status.
int hal_RegAnaInterrupt(hal_AnaInterrupt_t fp);

/// Write an analog output.
/// @param pin Specific pin number.
/// @param value Value to write.
/// @return Status.
int hal_WriteAna(unsigned int channel, uint16_t value);

/// Read an analog input.
/// @param pin Specific pin number.
/// @param value Where to place the value.
/// @return Status.
int hal_ReadAna(unsigned int channel, uint16_t* value);


//---------------- Serial Functions -----------------//

/// Open a serial port.
/// @param channel Specific channel.
/// @return Status.
int hal_SerOpen(unsigned int channel);

/// Read from a serial channel.
/// @param channel Specific channel.
/// @param buff Data buffer. Will be a zero-terminated string.
/// @param num Length of buff.
/// @return Status.
int hal_SerReadLine(unsigned int channel, char* buff, int num);

/// Write to a serial channel.
/// @param channel Specific channel.
/// @param buff What to send as a zero-terminated string.
/// @return Status.
int hal_SerWriteLine(unsigned int channel, char* buff);


//---------------- Timer Functions -----------------//

/// Timer interrupts.
/// @param period How oftern in msec.
/// @param fp Callback function.
/// @return Status.
int hal_RegTimerInterrupt(unsigned int period, hal_TimerInterrupt_t fp);

/// Get number of microseconds since beginning.
/// @return Microseconds.
uint64_t hal_GetCurrentUsec(void);

#endif // HAL_MODULE_H
