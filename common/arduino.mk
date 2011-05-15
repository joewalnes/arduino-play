CC       = avr-gcc
CXX      = avr-g++
CFLAGS   += -w -g -Os -ffunction-sections -fdata-sections -lm
CFLAGS   += -DBAUD=$(BAUD) -DF_CPU=$(F_CPU) -mmcu=$(MCU) -DARDUINO=22 -lm
CXXFLAGS += $(CFLAGS) -fno-exceptions

compile: app.hex
.PHONY: compile

%.hex: %.elf
	avr-objcopy -O ihex -R .eeprom $< $@

%.elf: $(wildcard *.c) $(wildcard *.cpp) 
	$(CC) $(CFLAGS) -s -o $@ $^

upload: app.hex
	avrdude -F -V -D -c $(PROTOCOL) -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$<
.PHONY: upload

serial:
	screen $(PORT) $(BAUD)
.PHONY: serial

clean:
	rm -rf $(wildcard *.elf) $(wildcard *.hex) build
.PHONY: clean

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

