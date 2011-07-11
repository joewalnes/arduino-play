ALLDEVICES = uno mini fio diamondback

# DEVICE=uno (Arduino UNO)
AVAILABLE_DEVICES += uno
ifeq ($(DEVICE),uno)
F_CPU=16000000L
MCU=atmega328p
PORT=/dev/tty.usbmodem*
BAUD=115200
PROTOCOL=stk500v1
DEVICE_SET=true
endif

# DEVICE=mini (Arduino Mini Pro)
AVAILABLE_DEVICES += mini
ifeq ($(DEVICE),mini)
F_CPU=16000000L
MCU=atmega328p
PORT=/dev/tty.usbserial*
BAUD=57600
PROTOCOL=stk500v1
DEVICE_SET=true
endif

# DEVICE=fio (Arduino Fio)
AVAILABLE_DEVICES += fio
ifeq ($(DEVICE),fio)
F_CPU=8000000L
MCU=atmega328p
PORT=/dev/tty.usbserial*
BAUD=57600
PROTOCOL=stk500v1
DEVICE_SET=true
endif

# DEVICE=diamond (Link Sprite Diamondback)
AVAILABLE_DEVICES += diamond
ifeq ($(DEVICE),diamond)
F_CPU=16000000L
MCU=atmega328p
PORT=/dev/tty.usbserial*
BAUD=57600
PROTOCOL=stk500v1
DEVICE_SET=true
endif

