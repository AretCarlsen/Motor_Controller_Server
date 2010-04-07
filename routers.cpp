/* ROUTERS */
  MAP::MAPPacketSink* raw_packetSinks[PACKET_SINK_COUNT];
  DataStore::ArrayBuffer<MAP::MAPPacketSink*, uint8_t> packetSinks(raw_packetSinks, PACKET_SINK_COUNT);

  // kernelSink is a Validator that sinks to kernelRouter.
  AddressGraph kernelRouter(KernelRouter_AddressType, KernelRouter_AddressValue, &packetSinks);
  // portRouter is just that.
  AddressGraph portRouter(PortRouter_AddressType, PortRouter_AddressValue, &packetSinks);

  // Everything that enters the kernelRouter must first be validated and stripped of checksums.
    // Static for auto-class access
  static MAP::PacketValidator kernelSink(&kernelRouter);

  // Outgoing chain: checksum generator to MEP encoder.
  MEP::MEPEncoder process_outgoingEncoder(&outputBuffer);
  MAP::OffsetMAPPacket raw_outgoing_packet_buffer[OUTGOING_PACKET_BUFFER_CAPACITY];
  MAP::MAPPacketBuffer process_outgoingPacketBuffer(&process_outgoingEncoder, raw_outgoing_packet_buffer, OUTGOING_PACKET_BUFFER_CAPACITY);
  // Static for access by inline classes
  static MAP::PacketChecksumGenerator outgoingSink(&process_outgoingPacketBuffer);

