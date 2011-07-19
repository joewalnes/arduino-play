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
  int year;   // e.g. 2011

  /**
   * Print data in human readable format to
   * output stream. e.g. data.print(&Serial);
   *
   * Example format: "2011/07/18 [Mon] 15:04:33"
   */
  void print(Print* out) {
    out->print(year);
    out->print("/");
    out->print(month);
    out->print("/");
    out->print(date);
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
    out->print(hour);
    out->print(":");
    out->print(minute);
    out->print(":");
    out->print(second);
  }

};
