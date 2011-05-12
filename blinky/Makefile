F_CPU=16000000L
MCU=atmega328p
PORT=/dev/tty.usbserial*
BAUD=57600
PROTOCOL=stk500v1

ARDSRC=../lib/arduino/cores/arduino

CC=avr-gcc
CXX=avr-g++
CFLAGS=-w -g -Os -ffunction-sections -fdata-sections -DF_CPU=$(F_CPU) -mmcu=$(MCU) -I$(ARDSRC) -DARDUINO=22 -lm
CXXFLAGS=$(CFLAGS) -fno-exceptions

APP=blinky

DEPS=$(wildcard $(ARDSRC)/*.c) $(wildcard $(ARDSRC)/*.cpp)

.PHONY: all clean upload

all: $(APP).hex

build/deps/arduinocore.a: $(DEPS)
	mkdir -p build/deps
	cp -R $^ build/deps
	ls build/deps/*.c   | sed -e 's/.c/.o/'   | xargs make
	ls build/deps/*.cpp | sed -e 's/.cpp/.o/' | xargs make
	(cd build/deps &&  avr-ar cq arduinocore.a *.o)

$(APP).elf: $(wildcard *.c) $(wildcard *.cpp) build/deps/arduinocore.a
	$(CC) $(CFLAGS) -s -o $@ $^

$(APP).hex: $(APP).elf
	avr-objcopy -O ihex -R .eeprom $< $@

clean:
	rm -rf $(wildcard *.elf) $(wildcard *.hex) build

upload: $(APP).hex
	avrdude -D -c $(PROTOCOL) -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$<

