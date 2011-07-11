/**
 * Allows a Nordic 2.4Ghz RF fob http://www.sparkfun.com/products/8602
 * to send commands to an Arduino using a transceiver:
 * http://www.sparkfun.com/products/152
 *
 * Wiring: (Arduino -> Tranceiver module)
 * 8 -> CE
 * 7 -> CSN
 * 11 -> MOSI
 * 12 -> MISO
 * 13 -> SCK
 * VCC (3.3V or 5V) -> VCC
 * GND -> GND
 */

#include <Arduino.h>
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

// key codes from Nordic fob
#define BUTTON_UP     0x1D
#define BUTTON_DOWN   0x1E
#define BUTTON_LEFT   0x17
#define BUTTON_RIGHT  0x1B
#define BUTTON_CENTER 0x0F

uint16_t htons(uint16_t v) { // big endian -> little endian
  return (v << 8) | (v >> 8);
}

// Message sent from fob
union {
  byte data[4]; // Raw data in
  struct { // Field values
    uint8_t button; // Code for button being pressed (see BUTTON_ constants above)
    uint16_t pressId; // ID that increments for each press. In big endian
    uint8_t pad; // Zero
  } msg;
} nordicIn;

uint16_t lastId;

void setup() {
  Serial.begin(BAUD);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte*)"ardui"); // Device ID. Doesn't matter what, but must be 5 chars.
  Mirf.configRegister(RF_SETUP, 0x07); // Data rate 1Mbit / 0dBm
  Mirf.configRegister(EN_AA, 0x00); // Disable auto-ack
  Mirf.payload = 4;
  Mirf.channel = 2;
  Mirf.config();
  Mirf.flushRx();
  Serial.println("Listening...");
}

void loop() {
  Mirf.getData(nordicIn.data);
  uint8_t pressId = htons(nordicIn.msg.pressId);
  if (pressId != lastId) {
    lastId = pressId;
    Serial.print(pressId);
    Serial.print(" ");
    Serial.print(lastId);
    Serial.print(" ");
    switch(nordicIn.msg.button) {
      case BUTTON_UP:
        Serial.print("U");
        break;
      case BUTTON_DOWN:
        Serial.print("D");
        break;
      case BUTTON_LEFT:
        Serial.print("L");
        break;
      case BUTTON_RIGHT:
        Serial.print("R");
        break;
      case BUTTON_CENTER:
        Serial.print("C");
        break;
      default: break; // no-op
    }
    Serial.println("");
  }
}
