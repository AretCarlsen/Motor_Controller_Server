// Copyright (C) 2010, Aret N Carlsen (aretcarlsen@autonomoustools.com).
// Motor Controller Server running under MapOS.
// Licensed under GPLv3 and later versions. See license.txt or <http://www.gnu.org/licenses/>.

// main() implementation.


// System timer
//#define SYSTEM_TIMER_FREQUENCY 12019   // Hertz
// Actually 83.2us
#define SYSTEM_TIMER_PERIOD_us 83      // Microseconds

// ADC channel count
#define ADC_CHANNEL_COUNT 2
// Number of raw readings that are averaged before sinking into the input buffers.
// About 12,019 readings occur per second (20MHz, /128 prescaler, 13 cycles per measurement),
// or one every 83.2us. Averaging 120 improves accuracy and cuts down to 100 measurements
// that must be processed each second, one very 10ms.
#define ADC_AVERAGED_READINGS 120
#define ADC_READING_PERIOD (ADC_AVERAGED_READINGS * SYSTEM_TIMER_PERIOD_us)

#define PRIMARY_MEMORY_POOL_LIMIT 1600

#define OUTGOING_PACKET_BUFFER_CAPACITY 3
#define INPUT_BUFFER_CAPACITY 50
#define OUTPUT_BUFFER_CAPACITY 100
#define UART_INITIAL_BAUD_RATE 115200

#include <ATcommon/arch/avr/avr.hpp>
#include <avrlib/rprintf.h>

// MapOS
#include <MapOS/arch/avr/main.hpp>
#include <MapOS/arch/avr/uart.hpp>
#include <MapOS/arch/avr/verify.hpp>

// MotorControllerServer
#include "../../main.hpp"
// Parameters
#include "../../parameters.hpp"

// PWM
#include "pwm.hpp"

// ADC setup
#include <MapOS/arch/avr/adc.hpp>

// No add'l packet sinks are introduced in this file.
#define INITIAL_PACKET_SINK_COUNT (MOTORCONTROLLER_PACKET_SINK_COUNT + 0)
// New processes defined in this file.
#define INITIAL_PROCESS_DEFINITION_COUNT (MOTORCONTROLLER_PROCESS_DEFINITION_COUNT + 1)

inline void init(){
// Global initializations
  init_UART();
  init_PWM();
  init_ADC();
 
  rprintfInit(uartSendByte);

// DEBUGprint init
//  init_DEBUGprint();
//  rprintf("*I\n");

// Wait for Eeprom to become available
  eeprom_busy_wait();

  verify_eeprom();
  verify_memPool();
}

void main(){
  init();
// Motor driver
  AVRServoDriver raw_motorDriver;

// Give the outgoing sink 50ms to simmer down...
  sleep_ms(50);

#include <MapOS/arch/avr/main.cpp>

#include "../../main.cpp"

  // Make sure outgoing data bus is triggered occasionally.
  scheduler.add_process(&process_triggerOutgoing, 500);

  DEBUGprint_RARE("Sched st\n");

  while(1){
    // Argument is in microseconds.
    scheduler.process(get_systemTime());
  }
}

