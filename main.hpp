
// AnalogEncoder, EncoderMonitor, EncoderMonitorServer
#include <Motion/AnalogEncoder/EepromAnalogEncoder.hpp>
// MotorDriver, MotorDriverServer
#include <Motion/MotorDriver/MotorDriverServer.hpp>
// PID engine
#include <Motion/PIDEngine/PIDEngine.hpp>
#include <Motion/PIDEngine/PIDEngineServer.hpp>
#include <Motion/PIDEngine/EepromPIDEngine.hpp>
// Oscilloscope (ADCserver)
#include <ATcommon/ADCServer/ADCServer.hpp>

#include "addresses.hpp"

typedef FixedPoint<int16_t, 14> PIDFpType;

#define MOTORCONTROLLER_PACKET_SINK_COUNT 6

#define MOTORCONTROLLER_PROCESS_DEFINITION_COUNT 7

