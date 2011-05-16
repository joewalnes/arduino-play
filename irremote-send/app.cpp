/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <Arduino.h>
#include <IRremote.h>

IRsend irsend;

void setup()
{
  Serial.begin(BAUD);
}

bool toggle = false;

void loop() {
  if (Serial.read() != -1) {
    Serial.println(toggle ? "ON!" : "OFF!");
    for (int i = 0; i < 3; i++) {
      irsend.sendNEC(toggle ? 0x4BB620DF : 0x4B36E21D, 32);
      delay(100);
    }
    toggle = !toggle;
  }
}
