#include <HughesyShiftBrite.h>

#include "RealTimeClock.h"
#include "Timer.h"

/**
 * <http://www.sparkfun.com/products/99>
 * Arduino -> Real Time Clock Module
 * -----------------
 * 5V -> 5V
 * Gnd -> Gnd
 * A4 -> SDA
 * A5 -> SCL
 *
 * <http://docs.macetech.com/doku.php/shiftbrite>
 * Arduino -> ShiftBrite
 * --------------------
 * 5V -> V+
 * GND -> GND
 * D10 -> D1
 * D11 -> L1
 * D12 -> E1
 * D13 -> C1
 */

void dumpTimeToSerial();
void toggleColor();

RealTimeClock rtc;
HughesyShiftBrite rgb;

Timer dumpTimer(1000, dumpTimeToSerial);
Timer toggleTimer(3000, toggleColor);

void setup(){
  rgb = HughesyShiftBrite();
  Serial.begin(BAUD);
  rtc.init();
  Serial.println("Clock started");
  rgb.sendColour(200, 0, 0);
}

void dumpTimeToSerial() {
  Serial.print("Current time: ");
  // Time from RTC module. ie. Real world time.
  DateTime now = rtc.getCurrentTime();
  now.print(&Serial);
  Serial.println();
}

bool isOn;

void toggleColor() {
  if (isOn) {
    Serial.println("Toggle on");
    rgb.sendColour(0, 600, 0);
  } else {
    Serial.println("Toggle off");
    rgb.sendColour(400, 0, 500);
  }
  isOn = !isOn;
}

void loop() {
  dumpTimer.run();
  toggleTimer.run();
}

