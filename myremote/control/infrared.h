#pragma once

#include <IRremote.h>

/**
 * IRremote library uses digital pin 3 for output
 */
class IrController {

  private:

    IRsend _irsend;

  public:

    void nec(int code) {
      for (int i = 0; i < 3; i++) {
        _irsend.sendNEC(code, 32);
        delay(100);
      }
    }

    void nec(int code1, int code2) {
      nec(code1);
      nec(code2);
    }

} ir;
