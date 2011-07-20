#pragma once

#include <Print.h>

/**
 * Holds a time (that is not associated with any particular date)
 */
struct Time {
  const int hour;   // 0-23
  const int minute; // 0-59
  const int second; // 0-59
  const int millisecond; // 0-999

  Time(int hour = 0, int minute = 0, int second = 0, int milliseconds = 0)
    : hour(hour), minute(minute), second(second), millisecond(millisecond) {}

  int value() const {
    return millisecond
      + second * 1000
      + minute * 1000 * 60
      + hour * 1000 * 60 * 60;
  }

};

// Overload comparison operators, so you can check Time(...) <= Time(...)
bool operator >  (const Time& t1, const Time& t2) { return t1.value() >  t2.value(); }
bool operator >= (const Time& t1, const Time& t2) { return t1.value() >= t2.value(); }
bool operator <  (const Time& t1, const Time& t2) { return t1.value() <  t2.value(); }
bool operator <= (const Time& t1, const Time& t2) { return t1.value() <= t2.value(); }
bool operator == (const Time& t1, const Time& t2) { return t1.value() == t2.value(); }
bool operator != (const Time& t1, const Time& t2) { return t1.value() != t2.value(); }


/**
 * Holds a date and time.
 */
struct DateTime {
  int year;   // 1-99 
  int month;  // 1-12
  int date;   // 0-31
  int day;    // 0-6 (sunday->saturday)
  int hour;   // 0-23
  int minute; // 0-59
  int second; // 0-59

  Time timeOfDay() const {
    return Time(hour, minute, second);
  }

  /**
   * Print data in human readable format to
   * output stream. e.g. data.print(&Serial);
   *
   * Example format: "2011/07/18 [Mon] 15:04:33"
   */
  void print(Print* out) const {
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
  static void pad(Print* out, int value) {
    if (value < 10) {
      out->print("0");
    }
    out->print(value);
  }
};
