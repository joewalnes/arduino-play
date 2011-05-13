include ../common/device.mk
include ../common/arduino.mk

CFLAGS += -I../lib/arduino/cores/arduino -I../common 

APP=blinky

.PHONY: all clean upload

all: $(APP).hex

build/deps/arduinocore.a: $(wildcard ../lib/arduino/cores/arduino/*.c) $(wildcard ../lib/arduino/cores/arduino/*.cpp)
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

