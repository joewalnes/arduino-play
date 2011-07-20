#pragma once

typedef unsigned long milliseconds;
typedef void (*timer_callback)();

/**
 * Simple timer class. Makes it easy to schedule work that
 * occurs at different intervals.
 *
 * Example usage:
 *
 *   // Functions you want to be called
 *   void doSomething() { ... }
 *   void somethingElse() { ... }
 *
 *   Timer timer;
 *
 *   // Setup timers
 *   void setup() {
 *     timer.schedule(250, doSomething); // Call doSomething() every 250 milliseconds
 *     timer.schedule(400, somethingElse); // every 400 milliseconds
 *   }
 *
 *   // Called repeatedly
 *   void loop() {
 *     timer.tick(); // Trigger your functions, if it's time
 *   }
 *
 * @author Joe Walnes
 */
class Timer {

  /**
   * Linked list of entries
   */
  struct Entry {
    Entry* nextEntry;
    milliseconds lastExecuteTime;
    milliseconds interval;
    timer_callback callback;
  };

  Entry* first;
  Entry* last;

public:

  Timer() : first(NULL), last(NULL) {}

  /**
   * Schedule a callback to occur repeatedly.
   */
  void schedule(milliseconds interval, timer_callback callback) {
    Entry* entry = (Entry*)malloc(sizeof(Entry)); // 'new' not supported on Arduino
    entry->lastExecuteTime = 0;
    entry->interval = interval;
    entry->callback = callback;
    entry->nextEntry = NULL;
    if (last == NULL) {
      last = first = entry;
    } else {
      last->nextEntry = entry;
      last = entry;
    }
  }

  /**
   * Call repeatedly to fire any callbacks that are due to be fired.
   */
  void tick(milliseconds now = millis()) {
    for (Entry* entry = first; entry != NULL; entry = entry->nextEntry) {
      if (now - entry->lastExecuteTime > entry->interval) {
        entry->callback();
        entry->lastExecuteTime = now;
      }
    }
  }

  /**
   * Arduino doesn't support destructors, so you have
   * to explicitly call this to free memory when you're done.
   * It's unlikely that you'll ever need this, but just in case.
   */
  void destroy() {
    Entry* entry = first;
    while (entry != NULL) {
      Entry* next = entry->nextEntry;
      free(entry);
      entry = next;
    }
    first = NULL;
    last = NULL;
  }

};
