// Copyright (C) 2010, Aret N Carlsen (aretcarlsen@autonomoustools.com).
// Motor Controller Server running under MapOS.
// Licensed under GPLv3 and later versions. See license.txt or <http://www.gnu.org/licenses/>.

// main() implementation.


#include <ATcommon/arch/linux/linux.hpp>

// ADC channel count
#define ADC_CHANNEL_COUNT 2
// Number of raw readings that are averaged before sinking into the input buffers.
// About 12,019 readings occur per second (20MHz, /128 prescaler, 13 cycles per measurement),
// or one every 83.2us. Averaging 120 improves accuracy and cuts down to 100 measurements
// that must be processed each second, one very 10ms.
#define ADC_AVERAGED_READINGS 120
#include "adc.hpp"

// Microseconds
#define SYSTEM_TIMER_PERIOD_us 1000
#define ADDL_PROCESS_DEFINITION_COUNT 8
#define PRIMARY_MEMORY_POOL_LIMIT 1600

#define OUTGOING_PACKET_BUFFER_CAPACITY 10
#define INPUT_BUFFER_CAPACITY 100
#define OUTPUT_BUFFER_CAPACITY 100

#define ADC_READING_PERIOD (241 * 83)

#include <stdlib.h>
#include <stdio.h>
#include <cstring>
// Threading
#include <pthread.h>

// No add'l packet sinks are introduced in this file.
#define INITIAL_PACKET_SINK_COUNT 10
// New processes defined in this file.
#define INITIAL_PROCESS_DEFINITION_COUNT 7
#include <MapOS/arch/linux/main.hpp>
#include "../../main.hpp"
// Parameters
#include "../../parameters.hpp"

// I/O
#include <MapOS/arch/linux/io.hpp>
#include <MapOS/arch/linux/threads.hpp>
// DebugServoDriver
#include "debugServoDriver.hpp"

int main(int argc, char **argv){
/* INIT */
  // If requested, redirect stderr to dev-null.
  if(argc > 1 && !strcmp(argv[1], "-s"))
    freopen("/dev/null", "a", stderr);

// Threads
  init();

  // Motor driver
  DebugServoDriver raw_motorDriver;

#include <MapOS/arch/linux/main.cpp>

#include "../../main.cpp"

// Main loop.
  DEBUGprint_RARE("Sched st\n");
  uint32_t last_tick = 0;
  while(1){
    uint32_t new_tick = get_systemTime();

    if(new_tick - last_tick >= ADC_READING_PERIOD){
//      DEBUGprint_RARE("ADC...");

//      adc_inputBuffers.get(0)->sinkData(128);
//      adc_inputBuffers.get(1)->sinkData(128);
 
      last_tick = new_tick;
    }

  // Simple timed scheduler.
    // Argument is in microseconds.
    scheduler.process(new_tick);

  // Linux: back off a bit. (Reduces x86 CPU usage from 100% to 9%.)
    usleep(100);
  }

  return 0;
}

