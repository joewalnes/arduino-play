include ../common/device.mk

ARDSRC=../lib/arduino/cores/arduino

CC=avr-gcc
CXX=avr-g++
CFLAGS=-w -g -Os -ffunction-sections -fdata-sections -DF_CPU=$(F_CPU) -mmcu=$(MCU) -I$(ARDSRC) -I../lib/IRremote -I../common -DARDUINO=22 -lm
CXXFLAGS=$(CFLAGS) -fno-exceptions

APP=remote

DEPS=$(wildcard $(ARDSRC)/*.c) $(wildcard $(ARDSRC)/*.cpp)

.PHONY: all clean upload

all: $(APP).hex

build/deps/arduinocore.a: $(DEPS)
	mkdir -p build/deps/arduinocore
	cp -R $^ build/deps/arduinocore
	ls build/deps/arduinocore/*.c   | sed -e 's/\.c/.o/'   | xargs make
	ls build/deps/arduinocore/*.cpp | sed -e 's/\.cpp/.o/' | xargs make
	(cd build/deps/arduinocore &&  avr-ar cq ../arduinocore.a *.o)

build/deps/irremote.a: ../lib/IRremote/*.cpp
	mkdir -p build/deps/irremote
	cp -R $^ build/deps/irremote
	ls build/deps/irremote/*.cpp | sed -e 's/.cpp/.o/' | xargs make
	(cd build/deps/irremote &&  avr-ar cq ../irremote.a *.o)

$(APP).elf: $(wildcard *.c) $(wildcard *.cpp) build/deps/irremote.a build/deps/arduinocore.a
	$(CC) $(CFLAGS) -s -o $@ $^

$(APP).hex: $(APP).elf
	avr-objcopy -O ihex -R .eeprom $< $@

clean:
	rm -rf $(wildcard *.elf) $(wildcard *.hex) build

upload: $(APP).hex
	avrdude -D -c $(PROTOCOL) -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$<

