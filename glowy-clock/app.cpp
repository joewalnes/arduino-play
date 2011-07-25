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
Timer timer;

void setup(){
  Serial.begin(BAUD);
  rgb = HughesyShiftBrite();
  rtc.init();
  Serial.println("Clock started");

  timer.schedule(1000, dumpTimeToSerial);
  timer.schedule(3000, updateColor);

  dumpTimeToSerial();
  updateColor();
}

void loop() {
  timer.tick();
}

void dumpTimeToSerial() {
  Serial.print("Current time: ");
  DateTime now = rtc.now(); // Time from RTC module. ie. Real world time.
  now.print(&Serial);
  Serial.println();
}

void updateColor() {
  DateTime now = rtc.now();
  Time time = now.timeOfDay();
  Color color = getGlowColor(time);
  rgb.sendColour(color.red, color.green, color.blue);

  /* Debug
  Serial.print("UPDATE: ");
  Serial.print(time.hour);
  Serial.print(":");
  Serial.print(time.minute);
  Serial.print(":");
  Serial.print(time.second);
  Serial.print(":");
  Serial.print(time.millisecond);
  Serial.print(" ");
  Serial.print(time.value());
  Serial.print(" ");
  Serial.print(color.red);
  Serial.print(",");
  Serial.print(color.green);
  Serial.print(",");
  Serial.print(color.blue);
  Serial.println();
  */
}

Color getGlowColor(Time time){
  //                   HH:MM                  RED GREEN  BLUE
  if      (time < Time(22    )
        && time > Time(19    )) return Color(  32,   32,   32); // Evening
  else if (time < Time( 5    )
        || time >= Time(22   )) return Color(   8,    0,    0); // Deep sleep
  else if (time < Time( 6    )) return Color( 128,   32,    0); // Dawn approaching
  else if (time < Time( 6, 30)) return Color(1023, 1023,    0); // Wake up time
  else if (time < Time( 7    )) return Color(   0, 1023,    0); // Wake up NOW!
  else if (time < Time(10    )) return Color(   0, 1023, 1023); // LATE!!!!
  else                          return Color(   0,    0,    0); // Daytime
}

