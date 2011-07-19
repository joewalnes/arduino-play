#pragma once

typedef unsigned long milliseconds;
typedef void (*timer_callback)();

/**
 * Simple timer class. Construct with callback function to run,
 * and interval, then call run() repeatedly and it will call
 * the callback every once in a while.
 */
class Timer {
  milliseconds last;
  milliseconds interval;
  timer_callback callback;

public:

  Timer(milliseconds interval, timer_callback callback)
    : last(0), interval(interval), callback(callback) {}

  void run() {
    run(millis());
  }

  void run(milliseconds now) {
    if (now - last > interval) {
      callback();
      last = now;
    }
  }

};
