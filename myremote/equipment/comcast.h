#pragma once

#include "core.h"

class Comcast {

  private:

    bool _on;

  public:

    void on() {
      if (!_on) {
        // Send Comcast PowerOn
        _on = true;
      }
    }

    void off() {
      // Send Comcast PowerOff
      _on = false;
    }

};

