// Copyright (C) 2010, Aret N Carlsen (aretcarlsen@autonomoustools.com).
// Motor Controller Server running under MapOS.
// Licensed under GPLv3 and later versions. See license.txt or <http://www.gnu.org/licenses/>.

// Debugging servo driver. Writes events out to the console.


#define TIMER1_TOP 49999
#define TIMER1_SERVO_MIN 2500
#define TIMER1_SERVO_NEUTRAL 3750
#define TIMER1_SERVO_MAX 4999
#define PWM_1A_INITIAL_VALUE TIMER1_SERVO_NEUTRAL
#define PWM_1B_INITIAL_VALUE TIMER1_SERVO_NEUTRAL
class DebugServoDriver : public ServoDriver {
  Output_t minOutput;
  Output_t maxOutput;

// For debugging
  uint16_t current_output;

public:

  DebugServoDriver(Output_t new_minOutput = MinOutput, Output_t new_maxOutput = MaxOutput)
  : minOutput(new_minOutput), maxOutput(new_maxOutput)
  { }

  void setOutput(Output_t new_output){
    DEBUGprint_MD("SD: oput to X%x\n", new_output.get_rawValue());

  // Limit output
    if(new_output > maxOutput)
      new_output = maxOutput;
    else if(new_output < minOutput)
      new_output = minOutput;

    DEBUGprint_MD("SD: Clamped to X%x (d%d)\n", new_output.get_rawValue(), new_output.get_rawValue());

  // Offset/Scale output
  // An oversimplification: Pretend that distance from neutral to max is same as from neutral to min.
    // Offset: This is the offset between the minimum raw output and the neutral position.
  // Inefficient to create an entire var just to pull its raw val back out. (If compiler is dumb.)
//    uint16_t scale = Output_t(1).get_rawValue() / (TIMER1_SERVO_MAX - TIMER1_SERVO_NEUTRAL);
    uint16_t scale = (1 << Output_t::SignificandBitCount) / (TIMER1_SERVO_MAX - TIMER1_SERVO_NEUTRAL);
    uint16_t offset = TIMER1_SERVO_MIN + (TIMER1_SERVO_MAX - TIMER1_SERVO_NEUTRAL);
    uint16_t raw_output = (int32_t) offset + ((int32_t) new_output.get_rawValue() / scale);

  //uartSendString("Set pow: ");
  //uartSendHex(new_output);

  // Set output
    if(raw_output != current_output){
      DEBUGprint_MD("SD: Scl %d, offset %d; set raw oput d%d\n", scale, offset, raw_output);
      current_output = raw_output;
    }

//DEBUGprint("ServoDriver: Raw output: %u\n", new_output);
//    new_output = (uint32_t) 2499 * new_output / 65535;
DEBUGprint_MD("ServoDriver: Setting output to %d\n", raw_output);
  }
};

