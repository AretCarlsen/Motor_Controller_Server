
// AnalogEncoder, EncoderMonitor, EncoderMonitorServer
#include "../AnalogEncoder/EepromAnalogEncoder.hpp"
// MotorDriver, MotorDriverServer
#include "../MotorDriver/MotorDriverServer.hpp"
// PID engine
#include "../PIDEngine/PIDEngine.hpp"
#include "../PIDEngine/PIDEngineServer.hpp"
#include "../PIDEngine/EepromPIDEngine.hpp"
// Oscilloscope (ADCserver)
#include "../ADCServer/ADCServer.hpp"

#include "addresses.hpp"

typedef FixedPoint<int16_t, 14> PIDFpType;

#define MOTORCONTROLLER_PACKET_SINK_COUNT 6

#define MOTORCONTROLLER_PROCESS_DEFINITION_COUNT 7

