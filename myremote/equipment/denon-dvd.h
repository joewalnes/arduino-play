#pragma once

#include "control/infrared.h"

class DenonDvd {

  private:

    bool _on;

  public:

    void on() {
      if (!_on) {
        // TODO: Send DVD PowerOn
        _on = true;
      }
    }

    void off() {
      // TODO: Send DVD PowerOff
      _on = false;
    }

};

