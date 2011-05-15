#include <Arduino.h>

#define PIN 13

void setup() {
  pinMode(PIN, OUTPUT);
}

void loop() {
  digitalWrite(PIN, (millis() / 500) % 2 ? HIGH : LOW);
}
