#pragma once

#include "control/infrared.h"

class RokuStreamer {

  public:

    void forceReset() {
    }

};

/*  
Play/Pause: NEC: 574332CD (32 bits)
<<: NEC: 57432CD3 (32 bits)
  repeat: NEC: 57432DD2 (32 bits)
>>: NEC: 5743AA55 (32 bits)
  repeat: NEC: 5743AB54 (32 bits)
Back: NEC: 57436699 (32 bits)
Home: NEC: 5743C03F (32 bits)
Replay: NEC: 57431EE1 (32 bits)
Options: NEC: 57438679 (32 bits)
Up: NEC: 57439867 (32 bits)
  repeat: NEC: 57439966 (32 bits)
Down: NEC: 5743CC33 (32 bits)
  repeat: NEC: 5743CD32 (32 bits)
Left: NEC: 57437887 (32 bits)
  repeat: NEC: 57437986 (32 bits)
Right: NEC: 5743B44B (32 bits)
  repeat: NEC: 5743B54A (32 bits)
OK: NEC: 574354AB (32 bits)
  repeat: NEC: 574355AA (32 bits)
*/
