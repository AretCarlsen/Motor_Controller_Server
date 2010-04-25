
#define ENCODER_COUNT 2

// Analog encoders, in Eeprom.
//AnalogEncoder::EncoderParameters eeprom_encoderParameters[ENCODER_COUNT] = {
int16_t int16_eeprom_encoderParameters[ENCODER_COUNT][sizeof(AnalogEncoder::EncoderParameters) / sizeof(int16_t)] EEMEM = {
// AllowedError (FP), offset, scale.
  { 0x0200, 366, -239 },
  { 0x0200, 366, -239 },
// ARE: { 0x0200, 398, -46 }
};
AnalogEncoder::EncoderParameters *eeprom_encoderParameters = (AnalogEncoder::EncoderParameters*) int16_eeprom_encoderParameters;

// PID parameters, in Eeprom.
//PID::PIDParameters<PIDFpType, PIDFpType> eeprom_pidParameters = {
int16_t EEMEM int16_eeprom_pidParameters[sizeof(PID::PIDParameters<PIDFpType,PIDFpType>) / sizeof(uint16_t)] EEMEM = {
// (all FP): MaxOutput, P_gain, I_gain, D_gain, errorIntegral_hysteresis, errorIntegral_saturationDecrease
//  0x1000, 0x1000, 0x0100, 0x0000, 0x0000, 0x0000
  0x4000, 0x0500, 0x0100, 0x0000, 0x1000, 0x0080
};
PID::PIDParameters<PIDFpType,PIDFpType> *eeprom_pidParameters = (PID::PIDParameters<PIDFpType,PIDFpType>*) int16_eeprom_pidParameters;

// Moved throttle curve control into ESC itself
  // Motor hysteresis, raw value (FP-14)
    // 0.01
//static const FixedPoint<int16_t, 14> motorHysteresis((1 << 14) / 100, true);
  // Motor offset, raw value (FP-14)
    // 0.10
//static const FixedPoint<int16_t, 14> motorOffset((1 << 14) / 10, true);

