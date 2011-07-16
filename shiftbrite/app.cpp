#include <Arduino.h>
#include "HughesyShiftBrite.h"

/**
 * Example showing how to drive a ShiftBrite RGB glowy
 * thingy <http://docs.macetech.com/doku.php/shiftbrite>
 * using the HughesyShiftBrite library.
 * <http://code.google.com/p/shiftbritehughesyarduino/>.
 *
 * Arduino -> ShiftBrite
 * --------------------
 * 5V -> V+
 * GND -> GND
 * D10 -> D1
 * D11 -> L1
 * D12 -> E1
 * D13 -> C1
 */
HughesyShiftBrite sb;

int maxVal = 1023;
int increment = 4;
const int DELAY_VAL = 1;

void setup() {
  sb = HughesyShiftBrite();
}

void loop() {
  for (int i = 0; i <= maxVal; i += increment) {
    sb.sendColour(i,0,0);
    delay(DELAY_VAL);
  }
  for (int i = maxVal; i > 0; i -= increment) {
    sb.sendColour(i,0,0);
    delay(DELAY_VAL);
  }
  for (int i = 0; i <= maxVal; i += increment) {
    sb.sendColour(0,i,0);
    delay(DELAY_VAL);
    Serial.println(i);
  }
  for (int i = maxVal; i > 0; i -= increment) {
    sb.sendColour(0,i,0);
    delay(DELAY_VAL);
  }
  for (int i = 0; i <= maxVal; i += increment) {
    sb.sendColour(0,0,i);
    delay(DELAY_VAL);
  }
  for (int i = maxVal; i > 0; i -= increment) {
    sb.sendColour(0,0,i);
    delay(DELAY_VAL);
  }
  for (int i = 0; i <= maxVal; i += increment) {
    sb.sendColour(i,i,0);
    delay(DELAY_VAL);
    Serial.println(i);
  }
  for (int i = maxVal; i > 0; i -= increment) {
    sb.sendColour(i,i,0);
    delay(DELAY_VAL);
  }
  for (int i = 0; i <= maxVal; i += increment) {
    sb.sendColour(i,0,i);
    delay(DELAY_VAL);
  }
  for (int i = maxVal; i > 0; i -= increment) {
    sb.sendColour(i,0,i);
    delay(DELAY_VAL);
  }
  for (int i = 0; i <= maxVal; i += increment) {
    sb.sendColour(0,i,i);
    delay(DELAY_VAL);
    Serial.println(i);
  }
  for (int i = maxVal; i > 0; i -= increment) {
    sb.sendColour(0,i,i);
    delay(DELAY_VAL);
  }
  for (int i = 0; i <= maxVal; i += increment) {
    sb.sendColour(i,i,i);
    delay(DELAY_VAL);
  }
  for (int i = maxVal; i > 0; i -= increment) {
    sb.sendColour(i,i,i);
    delay(DELAY_VAL);
  }
}

