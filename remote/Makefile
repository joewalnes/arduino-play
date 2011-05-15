# See ../README.txt

include ../common/device.mk
include ../common/arduino.mk

CFLAGS += -I../common 
CFLAGS += -I../lib/arduino/cores/arduino
CFLAGS += -I../lib/IRremote 

app.elf: build/deps/irremote.a build/deps/arduinocore.a

