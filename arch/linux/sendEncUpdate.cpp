
#include "../globals.hpp"
#include "../common/Packet/NP/NP.hpp"
#include "../common/Packet/MEP/MEPEncoder.hpp"
#include "../common/Packet/MAP/MAP.hpp"
#include "../common/DataStore/RingBuffer.hpp"
// ChecksumGenerator, Validator
#include "../common/Packet/PosixCRC32ChecksumEngine/PosixCRC32ChecksumEngine.hpp"

#include "../common/MotorControllerServer/addresses.hpp"

#define OUTPUT_BUFFER_CAPACITY 3000
uint8_t raw_outputBuffer[OUTPUT_BUFFER_CAPACITY];
DataStore::RingBuffer<uint8_t,uint8_t> outputBuffer(raw_outputBuffer, OUTPUT_BUFFER_CAPACITY);

#include <string.h>
int main(int argc, char **argv){
// If requested, redirect stderr to dev-null.
  if(argc > 1 && !strcmp(argv[1], "-s"))
    freopen("/dev/null", "a", stderr);

// Outgoing chain: checksum generator to MEP encoder.
  MEP::MEPEncoder process_outgoingEncoder(&outputBuffer);
// Static for access by inline classes
  static MAP::PacketChecksumGenerator outgoingSink(&process_outgoingEncoder);

// Allocate packet
  MAP::MAPPacket* packet;
  MAP::allocateNewPacket(&packet, 100);
  MAP::referencePacket(packet);

  packet->sinkData(MAP::NextProtoPresent_Mask | MAP::DestAddressPresent_Mask | LocalDevice_AddressType);
  // Next-proto
  packet->sinkData(MAP::Protocol__MAP);
  // Dest addy
  packet->sinkData(LocalDevice_AddressValue);


  // Inner headers
  packet->sinkData(MAP::DestAddressPresent_Mask | EncoderMonitor_Input_AddressType);
  // Dest addy
  packet->sinkData(EncoderMonitor_Input_Address);

  int32_t new_value;

#define ENCODER_COUNT 2
  packet->sinkC78(ENCODER_COUNT);
  for(uint8_t i = 0; i < ENCODER_COUNT; i++){
// Input
    scanf("%d", &new_value);
    DEBUGprint("Sinking enc %d: d:%d (X:%X)\n", i, new_value, new_value);
    packet->sinkC78(new_value);
  }

  outgoingSink.sinkPacket(packet);
  process_outgoingEncoder.process();  

  MAP::dereferencePacket(packet);

//DEBUGprint("outputBuffer.get_size() = %u\n", outputBuffer.get_size());
  uint8_t data;
  while(outputBuffer.sourceData(&data) == Status::Status__Good)
    putc(data, stdout);

  fflush(stdout);

  return 0;
}

