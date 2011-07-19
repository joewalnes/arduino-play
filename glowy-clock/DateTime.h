#pragma once

#include <Print.h>

/**
 * Holds a date and time.
 */
struct DateTime {
  int second; // 0-59
  int minute; // 0-59
  int hour;   // 0-23
  int day;    // 0-6 (sunday->saturday)
  int date;   // 0-31
  int month;  // 1-12
  int year;   // 1-99 

  /**
   * Print data in human readable format to
   * output stream. e.g. data.print(&Serial);
   *
   * Example format: "2011/07/18 [Mon] 15:04:33"
   */
  void print(Print* out) {
    out->print("20");
    pad(out, year);
    out->print("/");
    pad(out, month);
    out->print("/");
    pad(out, date);
    out->print(" [");
    switch (day) {
      case 0: out->print("Sun"); break;
      case 1: out->print("Mon"); break;
      case 2: out->print("Tue"); break;
      case 3: out->print("Wed"); break;
      case 4: out->print("Thu"); break;
      case 5: out->print("Fri"); break;
      case 6: out->print("Sat"); break;
    }
    out->print("] ");
    pad(out, hour);
    out->print(":");
    pad(out, minute);
    out->print(":");
    pad(out, second);
  }

private:
  void pad(Print* out, int value) {
    if (value < 10) {
      out->print("0");
    }
    out->print(value);
  }
};
