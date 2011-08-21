/**
 * Allows a Nordic 2.4Ghz RF fob http://www.sparkfun.com/products/8602
 * to have its commands related as HTTP requests
 * via an Arduino, Ethernet Shield and Nordic transceiver:
 * http://www.sparkfun.com/products/152
 *
 * Ethernet Shield should be stacked on top of Arduino.
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
#include <Ethernet.h>

// ---- Config ----
// Local Ethernet settings
byte localMac[] = {0xDE, 0xBB, 0xDA, 0xEF, 0xFE, 0xED};
byte localIp[] = {192, 168, 0, 191};
// Destination server
byte serverIp[] = {192, 168, 0, 104};
int serverPort = 9980;
// HTTP request. The button name (single char) will be sandwiched between these.
#define REQUEST_PREFIX "GET /buttonpress/"
#define REQUEST_SUFFIX " HTTP/1.0\r\n\r\n"
// ---- End Config ----

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
  Ethernet.begin(localMac, localIp);
  Serial.begin(BAUD);
  delay(1000); // Ethernet shield needs a moment...
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

void sendRequest(char cmd) {
  Serial.print("Send '");
  Serial.print(cmd);
  Serial.print("' : ");
  Client client(serverIp, serverPort);
  if (client.connect()) {
    client.print(REQUEST_PREFIX);
    client.print(cmd);
    client.print(REQUEST_SUFFIX);
    Serial.println("OK");
  } else {
    Serial.println("FAIL");
  }
  client.stop();
}

void loop() {
  Mirf.getData(nordicIn.data);
  uint8_t pressId = htons(nordicIn.msg.pressId);
  if (pressId != lastId) {
    lastId = pressId;
    switch(nordicIn.msg.button) {
      case BUTTON_UP    : sendRequest('U'); break;
      case BUTTON_DOWN  : sendRequest('D'); break;
      case BUTTON_LEFT  : sendRequest('L'); break;
      case BUTTON_RIGHT : sendRequest('R'); break;
      case BUTTON_CENTER: sendRequest('C'); break;
      default: break; // no-op
    }
  }
}
