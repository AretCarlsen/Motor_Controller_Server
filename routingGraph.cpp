
/* ROUTING GRAPH TARGETS */
  packetSinks.sinkData(&kernelSink);                    // 0
  packetSinks.sinkData(&portRouter);                    // 1
  packetSinks.sinkData(&outgoingSink);                  // 2
  packetSinks.sinkData(&process_echoServer);            // 3
  packetSinks.sinkData(&process_motorDriverServer);     // 4
  packetSinks.sinkData(&process_encoderMonitorServer);  // 5
  packetSinks.sinkData(&process_pidEngineInputServer);  // 6
  packetSinks.sinkData(&process_pidEngineTargetServer); // 7

/* INITIAL ROUTES */
  // Port router
    // Mode, Sink index, AddType, AddValue, AddValueMask, [HeaderOffset]
  // Local device address
  kernelRouter.sinkEdge(AddressFilter(AddressFilter::Mode__MaskedAddressValue,
                        1, LocalDevice_AddressType, LocalDevice_AddressValue, 0xFF, 1));
  // Anything with an outer address of DeviceLocal* or Topic
  kernelRouter.sinkEdge(AddressFilter(AddressFilter::Mode__AddressType,
                        1, MAP::AddressType__DeviceLocalStatic));
  kernelRouter.sinkEdge(AddressFilter(AddressFilter::Mode__AddressType,
                        1, MAP::AddressType__DeviceLocalDynamic));
  kernelRouter.sinkEdge(AddressFilter(AddressFilter::Mode__AddressType,
                        1, MAP::AddressType__Topic));

  // Outgoing bus (encoder)
    // Negated!
  kernelRouter.sinkEdge(AddressFilter(AddressFilter::Mode__MaskedAddressValue | AddressFilter::ModeMask__Negate,
                        2, LocalDevice_AddressType, LocalDevice_AddressValue, 0xFF));

  // Echo server
  portRouter.sinkEdge(AddressFilter(AddressFilter::Mode__MaskedAddressValue,
                      3,     EchoServer_Input_AddressType,     EchoServer_Input_Address, 0xFF));

  // Motor driver server
  portRouter.sinkEdge(AddressFilter(AddressFilter::Mode__MaskedAddressValue,
                      4,    MotorDriver_Input_AddressType,    MotorDriver_Input_Address, 0xFF));

  // Encoder monitor
  portRouter.sinkEdge(AddressFilter(AddressFilter::Mode__MaskedAddressValue,
                      5, EncoderMonitor_Input_AddressType, EncoderMonitor_Input_Address, 0xFF));

  // PID engine
  portRouter.sinkEdge(AddressFilter(AddressFilter::Mode__MaskedAddressValue,
                      6,      PIDEngine_Input_AddressType,      PIDEngine_Input_Address, 0xFF));

  // PID engine to MotorDriver
  portRouter.sinkEdge(AddressFilter(AddressFilter::Mode__MaskedAddressValue,
                      4,      PIDEngine_Output_AddressType,      PIDEngine_Output_Address, 0xFF));



