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
      _irsend.sendNEC(code, 32);
      shortPause();
    }

    void nec(unsigned long code1, unsigned long code2) {
      _irsend.sendNEC(code1, 32);
      _irsend.sendNEC(code2, 32);
      shortPause();
    }

    void shortPause() {
      delay(500);
    }

    void longPause() {
      delay(6000);
    }

} ir;
