#pragma once

#include "core.h"

class PanasonicTv {

  private:

    bool _on;
    int _current;

  public:

    void input(int number) {
      on();
      if (_current != number) {
        // Send Onkyo input N
        _current = number;
      }
    }

    void off() {
      // Send TV PowerOff
      _on = false;
    }

  private:

    void on() {
      if (!_on) {
        // Send TV PowerOn
        _on = true;
      }
    }
};

/*  
== TV ==
On: NEC: 55AA58A7 (32 bits)
Off: NEC: 55AAD827 (32 bits)
Input1: NEC: 55AA5AA5 (32 bits), NEC: F50A5EA1 (32 bits)
Input2: NEC: 55AA5AA5 (32 bits), NEC: F50ADE21 (32 bits)
Input3: NEC: 55AA5AA5 (32 bits), NEC: F50A3EC1 (32 bits)
Input4: NEC: 55AA5AA5 (32 bits), NEC: F50ABE41 (32 bits)
Input5: NEC: 55AA5AA5 (32 bits), NEC: F50A7E81 (32 bits)
Input6: NEC: 55AA5AA5 (32 bits), NEC: F50AFE01 (32 bits)
Screen size: NEC: 55AA7A85 (32 bits), NEC: F50A5CA3 (32 bits)
*/
