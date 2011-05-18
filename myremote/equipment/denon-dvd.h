#pragma once

#include "core.h"

class DenonDvd {

  private:

    bool _on;

  public:

    void on() {
      if (!_on) {
        // Send DVD PowerOn
        _on = true;
      }
    }

    void off() {
      // Send DVD PowerOff
      _on = false;
    }

};

