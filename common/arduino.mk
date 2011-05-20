CC       = avr-gcc
CXX      = avr-g++
CFLAGS   += $(INCLUDES) -w -g -Os -ffunction-sections -fdata-sections -lm
CFLAGS   += -DBAUD=$(BAUD) -DF_CPU=$(F_CPU) -mmcu=$(MCU) -DARDUINO=22 -lm
CXXFLAGS += $(CFLAGS) -fno-exceptions

include ../common/device.mk

ifneq ($(DEVICE_SET),true)
$(error Need to specify DEVICE (e.g. make DEVICE=foo ...). Available devices: $(AVAILABLE_DEVICES))
endif

compile: app.hex
.PHONY: compile

%.hex: %.elf
	avr-objcopy -O ihex -R .eeprom $< $@

%.elf: $(wildcard *.c) $(wildcard *.cpp) 
	$(CC) $(CFLAGS) -s -o $@ $^

upload: app.hex
	avrdude -F -V -D -c $(PROTOCOL) -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$<
.PHONY: upload

upload-usbtiny: app.hex
	avrdude -F -V -D -c usbtiny -p $(MCU) -U flash:w:$<
.PHONY: upload-usbtiny

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

build/deps/newsoftserial.a: ../lib/NewSoftSerial/*.cpp
	mkdir -p build/deps/newsoftserial
	cp -R $^ build/deps/newsoftserial
	ls build/deps/newsoftserial/*.cpp | sed -e 's/.cpp/.o/' | xargs make
	(cd build/deps/newsoftserial &&  avr-ar cq ../newsoftserial.a *.o)

build/deps/base64.a: ../lib/Base64/*.cpp ../lib/Base64/*.h
	mkdir -p build/deps/base64
	cp -R $^ build/deps/base64
	ls build/deps/base64/*.cpp | sed -e 's/.cpp/.o/' | xargs make
	(cd build/deps/base64 &&  avr-ar cq ../base64.a *.o)

build/deps/cmdmessenger.a: ../lib/CmdMessenger/*.cpp ../lib/CmdMessenger/*.h ../lib/Streaming/Streaming.h
	mkdir -p build/deps/cmdmessenger
	cp -R $^ build/deps/cmdmessenger
	ls build/deps/cmdmessenger/*.cpp | sed -e 's/.cpp/.o/' | xargs make INCLUDES=-Ibuild/deps/cmdmessenger
	(cd build/deps/cmdmessenger &&  avr-ar cq ../cmdmessenger.a *.o)


