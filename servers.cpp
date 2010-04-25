
// Oscilloscope
  ADCServer process_adcServer(&adc_inputBuffers, &kernelSink, &packet_memoryPool, ADCServer_Output_AddressType, ADCServer_Output_Address);

  ESCMotorDriver motorDriver(&raw_motorDriver);
// Moved throttle curve control into ESC itself.
//  ESCMotorDriver motorDriver(&raw_motorDriver, motorHysteresis, motorOffset);
  // Initial power: 0
  motorDriver.setPower(0);
  MotorDriverServer process_motorDriverServer(&motorDriver);

  AnalogEncoder::EepromEncoder eeprom_encoders[ENCODER_COUNT] = {
    AnalogEncoder::EepromEncoder(eeprom_encoderParameters),
    AnalogEncoder::EepromEncoder(eeprom_encoderParameters + 1)
  };
// Static for access by StateControlServer
  static AnalogEncoder::Encoder* encoders[ENCODER_COUNT] = {
    eeprom_encoders,
    eeprom_encoders + 1
  };

/*
// This can go after Eeprom saving in place.
//  DEBUGprint_RARE("Man calib st\n");
  encoders[0]->calibrate(571, 161);  // 48, 748
  encoders[1]->calibrate(571, 161);  // 48, 748
*/

  // Motor encoder monitor, sinking to kernel Validator.
    // Configure outgoing packet sink, encoder parameters, encoder count, and outgoing packet address type/value.
  AnalogEncoder::EncoderMonitor encoderMonitor(encoders, ENCODER_COUNT);
  AnalogEncoder::EncoderMonitorServer process_encoderMonitorServer(&encoderMonitor, &kernelSink, &packet_memoryPool, EncoderMonitor_Output_AddressType, EncoderMonitor_Output_Address);

// PID engine, sinking to kernel Validator.
  DEBUG_EEP(eeprom_pidParameters->debugPrintValues());
 // Static for access by StateControlServer
  static PID::EepromPIDEngine<PIDFpType,PIDFpType> pidEngine(eeprom_pidParameters);
  // Position input server. Configure outgoing packet sink, outgoing packet address type/value.
  PID::PIDEngineInputServer<PIDFpType, PIDFpType> process_pidEngineInputServer(&pidEngine, &kernelSink, &packet_memoryPool, PIDEngine_Output_AddressType, PIDEngine_Output_Address);
  // Setpoint (target) server. Takes the input server b/c that is who subtracts the current pos from the target.
  PID::PIDEngineTargetServer<PIDFpType, PIDFpType> process_pidEngineTargetServer(&process_pidEngineInputServer);
  // Parameter server.
  PID::PIDEngineParameterServer<PIDFpType, PIDFpType> process_pidEngineParameterServer(&pidEngine);

