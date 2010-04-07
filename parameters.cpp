
#define ENCODER_COUNT 2

// Analog encoders, in Eeprom.
//AnalogEncoder::EncoderParameters eeprom_encoderParameters[ENCODER_COUNT] = {
int16_t int16_eeprom_encoderParameters[ENCODER_COUNT][sizeof(AnalogEncoder::EncoderParameters) / sizeof(int16_t)] EEMEM = {
// AllowedError (FP), offset, scale.
// 1/256 (64 * 2^-14), 128, 39
  { 0x0040, 128, 39 },
// 1/256 (64 * 2^-14), 128, -39
  { 0x0040, 128, -39 },
};
AnalogEncoder::EncoderParameters *eeprom_encoderParameters = (AnalogEncoder::EncoderParameters*) int16_eeprom_encoderParameters;

// PID parameters, in Eeprom.
//PID::PIDParameters<PIDFpType, PIDFpType> eeprom_pidParameters = {
int16_t int16_eeprom_pidParameters[sizeof(PID::PIDParameters<PIDFpType,PIDFpType>) / sizeof(uint16_t)] EEMEM = {
// (all FP): MaxOutput, P_gain, I_gain, D_gain, errorIntegral_hysteresis, errorIntegral_saturationDecrease
  0x1000, 0x1000, 0x0100, 0x0000, 0x0000, 0x0000
//  PIDFpType(0x1000, true), PIDFpType(0x1000, true), PIDFpType(0x0100, true), 0x0000, 0x0000, 0x0000
};
PID::PIDParameters<PIDFpType,PIDFpType> *eeprom_pidParameters = (PID::PIDParameters<PIDFpType,PIDFpType>*) int16_eeprom_pidParameters;

// Motor hysteresis (= offset), raw value (FP-14)
static const FixedPoint<int16_t, 14> motorHysteresis(0x1000 / 3, true);

