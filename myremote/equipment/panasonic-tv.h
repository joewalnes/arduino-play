#pragma once

#include "control/infrared.h"

class PanasonicTv {

  private:

    bool _on;
    int _current;

  public:

    PanasonicTv() : _on(false), _current(0) {}

    void input(int number) {
      on();
      if (_current != number) {
        switch (number) {
          case 1: ir.nec(0x55AA5AA5, 0xF50A5EA1); break; // TV Input1
          case 2: ir.nec(0x55AA5AA5, 0xF50ADE21); break; // TV Input2
          case 3: ir.nec(0x55AA5AA5, 0xF50A3EC1); break; // TV Input3
          case 4: ir.nec(0x55AA5AA5, 0xF50ABE41); break; // TV Input4
          case 5: ir.nec(0x55AA5AA5, 0xF50A7E81); break; // TV Input5
          case 6: ir.nec(0x55AA5AA5, 0xF50AFE01); break; // TV Input6
        }
        _current = number;
      }
    }

    void off() {
      if (_on) {
        ir.nec(0x55AAD827); // TV PowerOff
        _on = false;
      }
    }

    void forceReset() {
      ir.nec(0x55AAD827); // TV PowerOff
      _on = false;
      _current = 0;
    }

    void changeScreenSize() {
      ir.nec(0x55AA7A85, 0xF50A5CA3); // TV ScreenSize
    }

  private:

    void on() {
      if (!_on) {
        ir.nec(0x55AA58A7); // TV PowerOn
        _on = true;
        ir.longPause();
      }
    }
};
