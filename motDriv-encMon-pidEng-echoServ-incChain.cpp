  ESCMotorDriver motorDriver(&raw_motorDriver, motorHysteresis);
  // Initial power: 0
  motorDriver.setPower(0);
  MotorDriverServer process_motorDriverServer(&motorDriver);

  AnalogEncoder::EepromEncoder eeprom_encoders[ENCODER_COUNT] = {
    AnalogEncoder::EepromEncoder(eeprom_encoderParameters),
    AnalogEncoder::EepromEncoder(eeprom_encoderParameters + 1)
  };
  AnalogEncoder::Encoder* encoders[ENCODER_COUNT] = {
    eeprom_encoders, eeprom_encoders + 1
  };

  // Motor encoder monitor, sinking to kernel Validator.
    // Configure outgoing packet sink, encoder parameters, encoder count, and outgoing packet address type/value.
  AnalogEncoder::EncoderMonitor encoderMonitor(encoders, ENCODER_COUNT);
  AnalogEncoder::EncoderMonitorServer process_encoderMonitorServer(&kernelSink, &encoderMonitor, EncoderMonitor_Output_AddressType, EncoderMonitor_Output_Address);

  DEBUGprint("Manual calibration...");
  for(uint8_t i = 0; i < ENCODER_COUNT; i++)
    encoders[i]->calibrate(128, 896);

  // PID engine, sinking to kernel Validator.
    // Configure PID parameters.
eeprom_pidParameters->debugPrintValues();
  PID::EepromPIDEngine<PIDFpType,PIDFpType> pidEngine(eeprom_pidParameters);
  // Position input server. Configure outgoing packet sink, outgoing packet address type/value.
  PID::PIDEngineInputServer<PIDFpType, PIDFpType> process_pidEngineInputServer(&pidEngine, &kernelSink, PIDEngine_Output_AddressType, PIDEngine_Output_Address);
  // Setpoint (target) server.
  PID::PIDEngineTargetServer<PIDFpType, PIDFpType> process_pidEngineTargetServer(&process_pidEngineInputServer);

  // Echo server, sinking to kernel Validator
  EchoServer process_echoServer(&kernelSink);

// Packets incoming from unreliable transmission media must include checksums.
  class : public MAP::MAPPacketSink { public: Status::Status_t sinkPacket(MAP::MAPPacket *packet, uint8_t headerOffset){
    // Header must exist and include a csum.
    MAP::Data_t *header = packet->get_header(headerOffset);
    // Note that kernel sink will actually verify checksum.
    if( header != NULL && MAP::get_checksumPresent(*header))
      kernelSink.sinkPacket(packet, headerOffset);

    return Status::Status__Good;
  } } incoming_checksumValidator;

// Incoming chain: MEP decoder to checksum validator.
// Static for access by inline classes
  static MEP::MEPDecoder incomingDecoder(&incoming_checksumValidator);
  class : public Process { public: Status::Status_t process(){
      uint8_t byte;
      while(
           (inputBuffer.sourceData(&byte) == Status::Status__Good)
        && (incomingDecoder.sinkData(byte) == Status::Status__Good)
      );
      return Status::Status__Good;
  } } process_incomingDecoder;


