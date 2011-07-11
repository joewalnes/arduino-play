# See ../README.txt
include ../common/arduino.mk

CFLAGS += -I../common 
CFLAGS += -I../lib/arduino/cores/arduino
CFLAGS += -I../lib/SPI
CFLAGS += -I../lib/Mirf

app.elf: build/deps/mirf.a build/deps/spi.a build/deps/arduinocore.a

