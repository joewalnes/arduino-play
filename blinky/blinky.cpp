#include <Arduino.h>

void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, (millis() / 500) % 2 ? HIGH : LOW);
}
