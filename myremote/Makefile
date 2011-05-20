# See ../README.txt
include ../common/arduino.mk

CFLAGS += -I../common 
CFLAGS += -I../lib/arduino/cores/arduino
CFLAGS += -I../lib/IRremote
CFLAGS += -I../lib/Streaming
CFLAGS += -I../lib/CmdMessenger
CFLAGS += -I.

app.elf: build/deps/irremote.a build/deps/cmdmessenger.a build/deps/arduinocore.a

