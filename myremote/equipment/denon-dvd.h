#pragma once

#include "control/infrared.h"

class DenonDvd {

  private:

    bool _on;

  public:

    DenonDvd() : _on(false) {}

    void on() {
      if (!_on) {
        // TODO: Send DVD PowerOn
        _on = true;
      }
    }

    void off() {
      if (_on) {
         // TODO: Send DVD PowerOff
         _on = false;
      }
    }

    void forceReset() {
      // TODO: Send DVD PowerOff
      _on = false;
    }

};

