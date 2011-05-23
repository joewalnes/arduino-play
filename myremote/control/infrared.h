#pragma once

#include <IRremote.h>

/**
 * IRremote library uses digital pin 3 for output
 */
class IrController {

  private:

    IRsend _irsend;

  public:

    void nec(unsigned long code) {
      for (int i = 0; i < 3; i++) {
        _irsend.sendNEC(code, 32);
        delay(100);
      }
      shortPause();
    }

    void nec(unsigned long code1, unsigned long code2) {
      nec(code1);
      nec(code2);
    }

    void shortPause() {
      delay(500);
    }

    void longPause() {
      delay(1500);
    }
} ir;
