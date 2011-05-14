# See ../README.txt

APP=serial

include ../common/device.mk
include ../common/arduino.mk

CFLAGS += -I../common 
CFLAGS += -I../lib/arduino/cores/arduino

$(APP).elf: build/deps/arduinocore.a
