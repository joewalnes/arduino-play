include ../common/device.mk
include ../common/arduino.mk

CFLAGS += -I../common 
CFLAGS += -I../lib/arduino/cores/arduino
CFLAGS += -I../lib/IRremote 

APP=remote

.PHONY: all clean upload

all: $(APP).hex

build/deps/arduinocore.a: $(wildcard ../lib/arduino/cores/arduino/*.c) $(wildcard ../lib/arduino/cores/arduino/*.cpp)
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

clean:
	rm -rf $(wildcard *.elf) $(wildcard *.hex) build

upload: $(APP).hex
	avrdude -D -c $(PROTOCOL) -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$<

