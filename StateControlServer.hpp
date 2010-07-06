// Copyright (C) 2010, Aret N Carlsen (aretcarlsen@autonomoustools.com).
// Motor Controller Server running under MapOS.
// Licensed under GPLv3 and later versions. See license.txt or <http://www.gnu.org/licenses/>.


// Nonvolatile state control server.

#include <MapOS/StateControlServer.hpp>

class LocalStateControlServer : public StateControlServer { public:
// Save realtime state to nonvolatile store
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

