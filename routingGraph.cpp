// Copyright (C) 2010, Aret N Carlsen (aretcarlsen@autonomoustools.com).
// Motor Controller Server running under MapOS.
// Licensed under GPLv3 and later versions. See license.txt or <http://www.gnu.org/licenses/>.

// Dynamic routing graph targets.


// Motor driver
  packetSinks.setExpand(4, &process_motorDriverServer);
// Encoder monitor
  packetSinks.setExpand(5, &process_encoderMonitorServer);
// PID engine: Input
  packetSinks.setExpand(6, &process_pidEngineInputServer);
// PID engine: Target (setpoint)
  packetSinks.setExpand(7, &process_pidEngineTargetServer);
// PID engine: Parameters
  packetSinks.setExpand(8, &process_pidEngineParameterServer);
// PID engine: State control (save/load)
  packetSinks.setExpand(9, &process_stateControlServer);

