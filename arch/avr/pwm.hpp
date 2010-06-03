#define TIMER1_TOP 49999
#define TIMER1_SERVO_MIN 2500
#define TIMER1_SERVO_NEUTRAL 3750
#define TIMER1_SERVO_MAX 4999
#define PWM_1A_INITIAL_VALUE TIMER1_SERVO_NEUTRAL
#define PWM_1B_INITIAL_VALUE TIMER1_SERVO_NEUTRAL


inline void set_ICR1(uint16_t new_value){
  ICR1H = new_value >> 8;
  ICR1L = new_value;
}
inline void set_OCR1A(uint16_t new_value){
// Safely output new counter comparator setting
  OCR1AH = new_value >> 8;
  OCR1AL = new_value;
}
inline void set_PWM_1A(uint16_t new_value){
  set_OCR1A(new_value);
}
inline void set_OCR1B(uint16_t new_value){
// Safely output new counter comparator setting
  OCR1BH = new_value >> 8;
  OCR1BL = new_value;
}
inline void set_PWM_1B(uint16_t new_value){
  set_OCR1B(new_value);
}

void init_PWM(){
// Initialize 16-bit PWM
  // Control registers
  TCCR1A = 0;
  TCCR1B = 0;
  TIMSK1 = 0;
  // Top, for 50Hz output
  set_ICR1(TIMER1_TOP);
  // Initial values
  set_PWM_1A(PWM_1A_INITIAL_VALUE);
  set_PWM_1B(PWM_1B_INITIAL_VALUE);
// Need to operate in mode 14 s.t. ICR1 is TOP. So WGM13|WGM12|WGM11; clear WGM10.
  sbi(TCCR1B, WGM13);
  sbi(TCCR1B, WGM12);
  sbi(TCCR1A, WGM11);
  cbi(TCCR1A, WGM10);
// COM1x0 off, COM1x1 on for clear-on-match.
  cbi(TCCR1A,COM1A0);
  sbi(TCCR1A,COM1A1);
  cbi(TCCR1A,COM1B0);
  sbi(TCCR1A,COM1B1);
// For clock div factor of 8, need CS12=0,CS11=1,CS10=0.
  cbi(TCCR1B, CS12);
  sbi(TCCR1B, CS11);
  cbi(TCCR1B, CS10);
// To interrupt on overflow, TOIE1.
//  sbi(TIMSK1, TOIE1);
// PB1 needs to be an output for OC1A.
  sbi(DDRB, PB1);
  sbi(DDRB, PB2);
}

class AVRServoDriver : public ServoDriver {
  Output_t minOutput;
  Output_t maxOutput;

// For debugging
  uint16_t current_output;

public:

  AVRServoDriver(Output_t new_minOutput = MinOutput, Output_t new_maxOutput = MaxOutput)
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
    set_PWM_1A(raw_output);
  }
};

