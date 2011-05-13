include ../common/device.mk
include ../common/arduino.mk

CFLAGS += -I../common 
CFLAGS += -I../lib/arduino/cores/arduino

APP=blinky

.PHONY: all clean upload

all: $(APP).hex

$(APP).elf: $(wildcard *.c) $(wildcard *.cpp) build/deps/arduinocore.a

clean:
	rm -rf $(wildcard *.elf) $(wildcard *.hex) build

upload: $(APP).hex
	avrdude -D -c $(PROTOCOL) -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$<

