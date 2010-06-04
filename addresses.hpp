// Copyright (C) 2010, Aret N Carlsen (aretcarlsen@autonomoustools.com).
// Motor Controller Server running under MapOS.
// Licensed under GPLv3 and later versions. See license.txt or <http://www.gnu.org/licenses/>.


// Local addresses.

#define ADCServer_Output_AddressType MAP::AddressType__Topic
#define ADCServer_Output_Address 19

#define EncoderMonitor_Output_AddressType MAP::AddressType__Topic
#define EncoderMonitor_Output_Address 21

#define PIDEngine_Output_AddressType MAP::AddressType__Topic
#define PIDEngine_Output_Address 23

#define PIDEngine_Parameter_AddressType MAP::AddressType__Topic
#define PIDEngine_Parameter_Address 25
#define PIDEngine_Target_AddressType MAP::AddressType__Topic
#define PIDEngine_Target_Address 26

#define LocalDevice_AddressType MAP::AddressType__LANLocal
#define LocalDevice_AddressValue 15

/*
#define EncoderMonitor_Input_AddressType MAP::AddressType__Topic
#define EncoderMonitor_Input_Address 20
#define PIDEngine_Input_AddressType MAP::AddressType__Topic
#define PIDEngine_Input_Address 22
#define MotorDriver_Input_AddressType MAP::AddressType__Topic
#define MotorDriver_Input_Address 24
#define EchoServer_Input_AddressType MAP::AddressType__DeviceLocalStatic
#define EchoServer_Input_Address 4
*/

#define StateControlServer_Input_AddressType MAP::AddressType__DeviceLocalStatic
#define StateControlServer_Input_Address 27


