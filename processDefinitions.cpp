// Copyright (C) 2010, Aret N Carlsen (aretcarlsen@autonomoustools.com).
// Motor Controller Server running under MapOS.
// Licensed under GPLv3 and later versions. See license.txt or <http://www.gnu.org/licenses/>.

// Routing graph.


// Echo server doesn't need to respond very quickly. 30ms period.
//  scheduler.add_process(&process_echoServer, 30000);
// State control server doesn't need to respond very quickly.
scheduler.add_process(&process_stateControlServer, 500000);
// PID parameter control server.
scheduler.add_process(&process_pidEngineParameterServer, 15000);

// Servers

// Update the PID engine target, if applicable.
scheduler.add_process(&process_pidEngineTargetServer, ADC_READING_PERIOD);
// Perform oscilloscope-style readings on the motor encoders.
// Measurements are broadcast in a Topic.
scheduler.add_process(&process_adcServer, ADC_READING_PERIOD);  //DEBUG 100000
// Receive motor encoder measurements and map/integrate to determine new position.
// Position is then broadcast in a Topic.
scheduler.add_process(&process_encoderMonitorServer, ADC_READING_PERIOD);
// Receive position and feed through a PID engine to calculate a new motor power.
// Motor power is then broadcast in a Topic.
scheduler.add_process(&process_pidEngineInputServer, ADC_READING_PERIOD);
// Receive motor power command and implement (via PWM output).
scheduler.add_process(&process_motorDriverServer, ADC_READING_PERIOD);


