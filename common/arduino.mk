CC       = avr-gcc
CXX      = avr-g++
CFLAGS   += -w -g -Os -ffunction-sections -fdata-sections -DF_CPU=$(F_CPU) -mmcu=$(MCU) -DARDUINO=22 -lm
CXXFLAGS += $(CFLAGS) -fno-exceptions

%.hex: %.elf
	avr-objcopy -O ihex -R .eeprom $< $@

