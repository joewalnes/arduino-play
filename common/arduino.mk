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

build/deps/spi.a: ../lib/SPI/*.cpp ../lib/SPI/*.h 
	mkdir -p build/deps/spi
	cp -R $^ build/deps/spi
	ls build/deps/spi/*.cpp | sed -e 's/.cpp/.o/' | xargs make
	(cd build/deps/spi &&  avr-ar cq ../spi.a *.o)

build/deps/eeprom.a: ../lib/EEPROM/*.cpp ../lib/EEPROM/*.h 
	mkdir -p build/deps/eeprom
	cp -R $^ build/deps/eeprom
	ls build/deps/eeprom/*.cpp | sed -e 's/.cpp/.o/' | xargs make
	(cd build/deps/eeprom &&  avr-ar cq ../eeprom.a *.o)

build/deps/sd.a: ../lib/SD/*.cpp ../lib/SD/*.h
	mkdir -p build/deps/sd
	cp -R $^ ../lib/SD/utility build/deps/sd
	ls build/deps/sd/*.cpp | sed -e 's/.cpp/.o/' | xargs make INCLUDES=-Ibuild/deps/sd
	(cd build/deps/sd &&  avr-ar cq ../sd.a *.o)

build/deps/ethernet.a: ../lib/Ethernet/*.cpp ../lib/Ethernet/*.h ../lib/SPI/SPI.h
	mkdir -p build/deps/ethernet
	cp -R $^ ../lib/Ethernet/utility build/deps/ethernet
	ls build/deps/ethernet/*.cpp | sed -e 's/.cpp/.o/' | xargs make INCLUDES="-Ibuild/deps/ethernet -Ibuild/deps/ethernet/utility"
	(cd build/deps/ethernet &&  avr-ar cq ../ethernet.a *.o)

build/deps/ethernetdhcp.a: ../lib/EthernetDHCP/*.cpp ../lib/EthernetDHCP/*.h
	mkdir -p build/deps/ethernetdhcp
	cp -R $^ ../lib/EthernetDHCP/utility build/deps/ethernetdhcp
	ls build/deps/ethernetdhcp/*.cpp | sed -e 's/.cpp/.o/' | xargs make INCLUDES=-Ibuild/deps/ethernetdhcp
	(cd build/deps/ethernetdhcp &&  avr-ar cq ../ethernetdhcp.a *.o)

build/deps/ethernetdns.a: ../lib/EthernetDNS/*.cpp ../lib/EthernetDNS/*.h
	mkdir -p build/deps/ethernetdns
	cp -R $^ ../lib/EthernetDNS/utility build/deps/ethernetdns
	ls build/deps/ethernetdns/*.cpp | sed -e 's/.cpp/.o/' | xargs make INCLUDES=-Ibuild/deps/ethernetdns
	(cd build/deps/ethernetdns &&  avr-ar cq ../ethernetdns.a *.o)

build/deps/ethernetbonjour.a: ../lib/EthernetBonjour/*.cpp ../lib/EthernetBonjour/*.h
	mkdir -p build/deps/ethernetbonjour
	cp -R $^ ../lib/EthernetBonjour/utility build/deps/ethernetbonjour
	ls build/deps/ethernetbonjour/*.cpp | sed -e 's/.cpp/.o/' | xargs make INCLUDES=-Ibuild/deps/ethernetbonjour
	(cd build/deps/ethernetbonjour &&  avr-ar cq ../ethernetbonjour.a *.o)



