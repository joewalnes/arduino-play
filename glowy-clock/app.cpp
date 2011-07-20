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

struct Color {
  int red;
  int green;
  int blue;
  Color(int r, int g, int b) : red(r), green(g), blue(b) {}
};

void dumpTimeToSerial();
void updateColor();
Color getGlowColor(Time time);

RealTimeClock rtc;
HughesyShiftBrite rgb;

Timer dumpTimer(1000, dumpTimeToSerial);
Timer updateColorTimer(3000, updateColor);

void setup(){
  rgb = HughesyShiftBrite();
  Serial.begin(BAUD);
  rtc.init();
  Serial.println("Clock started");
  rgb.sendColour(200, 0, 0);
}

void loop() {
  dumpTimer.run();
  updateColorTimer.run();
}

void dumpTimeToSerial() {
  Serial.print("Current time: ");
  // Time from RTC module. ie. Real world time.
  DateTime now = rtc.now();
  now.print(&Serial);
  Serial.println();
}

void updateColor() {
  DateTime now = rtc.now();
  Time time = now.timeOfDay();
  Color color = getGlowColor(time);
  rgb.sendColour(color.red, color.green, color.blue);
}

Color getGlowColor(Time time){
  //                   HH:MM                  RED GREEN  BLUE
  if      (time < Time(23, 30)
        && time > Time(10))     return Color( 256,  265,  256); // Evening          (white/dim)
  else if (time < Time( 4, 30)) return Color( 256,    0,    0); // Deep sleep       (red/dim)
  else if (time < Time( 6    )) return Color( 512,  512,    0); // Dawn approaching (yellow/medium)
  else if (time < Time( 6, 30)) return Color(1023, 1023,    0); // Wake up time     (yellow/bright)
  else if (time < Time( 7    )) return Color(   0, 1023,    0); // Wake up NOW!     (green/bright)
  else if (time < Time(10    )) return Color(1023,    0, 1023); // LATE!!!!         (purple/bright)
  else                          return Color(   0,    0,    0); // Daytime          (OFF)
}


