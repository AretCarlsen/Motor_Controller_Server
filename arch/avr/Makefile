# Aret N Carlsen (aret@ncarlsen.net)
#
# Makefile for motor controller server
#
# Last mod: 2010-05


#DEBUG = -DDEBUG
PROGRAM = server
SRC     = server.cpp
all: server.hex server.eep 

OBJS = virtual.o MemoryPool.o rprintf.o
OBJS += MEPEncoder.o MEPDecoder.o PosixCRC32Checksum.o SimpleServer.o MAP.o AddressGraph.o
OBJS += MotorDriverServer.o AnalogEncoder.o ADCServer.o
OBJS += templateInstantiations.o

PROJROOT = /root/Projects
IROOT = -I $(PROJROOT)
IPATH = $(IROOT) -I .

ARCH = avr

VPATH = .
VPATH += $(PROJROOT)/avrlib:$(PROJROOT)/ATcommon/arch/$(ARCH):$(PROJROOT)/ATcommon/MemoryPool/arch/$(ARCH):$(PROJROOT)/ATcommon/arch/$(ARCH)/virtual
VPATH += $(PROJROOT)/Upacket/MEP/arch/$(ARCH):$(PROJROOT)/Upacket/MAP/arch/$(ARCH):$(PROJROOT)/Upacket/PosixCRC32ChecksumEngine/arch/$(ARCH)
VPATH += $(PROJROOT)/Upacket/Servers/arch/$(ARCH):$(PROJROOT)/Upacket/Routing/arch/$(ARCH)
VPATH += $(PROJROOT)/Motion/MotorDriver/arch/$(ARCH):$(PROJROOT)/Motion/AnalogEncoder/arch/$(ARCH):$(PROJROOT)/ATcommon/ADCServer/arch/$(ARCH)

include $(PROJROOT)/ATcommon/arch/$(ARCH)/Makefile.inc

