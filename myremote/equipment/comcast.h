#pragma once

#include "control/infrared.h"

class Comcast {

  private:

    bool _on;

  public:

    Comcast() : _on(false) {}

    void on() {
      if (!_on) {
        // TODO: Send Comcast PowerOn
        _on = true;
      }
    }

    void off() {
      // TODO: Send Comcast PowerOff
      _on = false;
    }

};

