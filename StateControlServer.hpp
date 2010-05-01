#include "../MapOS/StateControlServer.hpp"

class LocalStateControlServer : public StateControlServer { public:
  void saveState(){
    //DEBUGprint_EEP("SCS:proc: md_sv %d\n", (mode_save? 1 : 0));
    kernelRouter_eepromStore.saveState();
    pidEngine.saveState();
    for(uint8_t i = 0; i < ENCODER_COUNT; i++)
      encoders[i]->saveState();
  }

  void loadState(){
    kernelRouter_eepromStore.loadState();
    pidEngine.loadState();
    for(uint8_t i = 0; i < ENCODER_COUNT; i++)
      encoders[i]->loadState();
  }
} process_stateControlServer;

