// Motor simulator

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

// Outgoing packet
  MAP::MAPPacket* packet;
  MAP::allocateNewPacket(&packet, 100);

  packet->sinkData(MAP::NextProtoPresent_Mask | MAP::DestAddressPresent_Mask | MAP::AddressType__LANLocal);
  // Next-proto
  packet->sinkData(MAP::Protocol__MAP);
  // Dest addy
  packet->sinkData(ADDRESS__DeviceLANLocal);


  // Inner headers
  packet->sinkData(MAP::DestAddressPresent_Mask | PIDEngine_Input_AddressType);
  // Dest addy
  packet->sinkData(PIDEngine_Input_Address);

  // Data
  int16_t new_value = 0;
  for(uint8_t i = 4; i > 0; i--){
    new_value <<= 4;
    char ch = getchar();
    if(ch >= '0' && ch <= '9')
      new_value |= ch - '0';
    else
      new_value |= ch - 'A' + 10;
  }
DEBUGprint("New input: %X\n", new_value);
  packet->sinkC78Signed(new_value);

  // Elapsed time
  new_value = 0;
  for(uint8_t i = 4; i > 0; i--){
    new_value <<= 4;
    char ch = getchar();
    if(ch >= '0' && ch <= '9')
      new_value |= ch - '0';
    else
      new_value |= ch - 'A' + 10;
  }
DEBUGprint("New elapsed time: %X\n", new_value);
  packet->sinkC78Signed(new_value);

  MAP::referencePacket(packet);
  outgoingSink.sinkPacket(packet);
  MAP::dereferencePacket(packet);
  process_outgoingEncoder.process();  

//DEBUGprint("outputBuffer.get_size() = %u\n", outputBuffer.get_size());
  uint8_t data;
  while(outputBuffer.sourceData(&data) == Status::Status__Good)
    putc(data, stdout);

  fflush(stdout);

  return 0;
}

