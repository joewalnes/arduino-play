#pragma once

#include <Arduino.h>
#include <Wire.h>

#include "DateTime.h"

/**
 * Interface with DS1307 Real Time Clock module
 * <http://www.sparkfun.com/products/99>
 *
 * This tutorial told me everything I needed to know:
 * http://bildr.org/2011/03/ds1307-arduino/
 *
 * Uses the I2C Wire library (bundled with Arduino SDK).
 *
 * Arduino -> Module connections
 * -----------------------------
 * 5V -> 5V
 * Gnd -> Gnd
 * A4 -> SDA
 * A5 -> SCL
 *
 * Usage:
 *   RealTimeClock rtc;
 *
 *   In setup() call rtc.init() to ensure the Wire
 *   library is setup correctly.
 *
 *   To read the time:
 *     DateTime now = rtc.getCurrentTime();
 *     now.print(Serial); // Print the time to serial port
 *     int hour = now.hour; // See DateTime.h for full reference
 */
class RealTimeClock {

  static const int DS1307_ADDRESS = 0x68;

public:

  void init() {
    Wire.begin();
  }

  /**
   * Reads current time from RTC module.
   */
  DateTime now() {
    // Reset the register pointer
    Wire.beginTransmission(DS1307_ADDRESS);
    Wire.send(0);
    Wire.endTransmission();

    Wire.requestFrom(DS1307_ADDRESS, 7);

    DateTime result;
    result.second = bcdToDec(Wire.receive());
    result.minute = bcdToDec(Wire.receive());
    result.hour = bcdToDec(Wire.receive() & 0b111111);
    result.day = bcdToDec(Wire.receive());
    result.date = bcdToDec(Wire.receive());
    result.month = bcdToDec(Wire.receive());
    result.year = bcdToDec(Wire.receive()) + 2000;

    return result;
  }

  /**
   * Sets the clock.
   */
  void setCurrentTime(DateTime time){
    Wire.beginTransmission(DS1307_ADDRESS);
    Wire.send(0); //stop Oscillator

    Wire.send(decToBcd(time.second));
    Wire.send(decToBcd(time.minute));
    Wire.send(decToBcd(time.hour));
    Wire.send(decToBcd(time.day));
    Wire.send(decToBcd(time.date));
    Wire.send(decToBcd(time.month));
    Wire.send(decToBcd(time.year) - 2000);

    Wire.send(0); //start 

    Wire.endTransmission();
  }

private:

  /**
   * Convert binary coded decimal to normal decimal numbers
   */
  byte bcdToDec(byte val) {
    return (val/16*10) + (val%16);
  }

  /**
   * Convert normal decimal numbers to binary coded decimal
   */
  byte decToBcd(byte val) {
    return (val/10*16) + (val%10);
  }

};

