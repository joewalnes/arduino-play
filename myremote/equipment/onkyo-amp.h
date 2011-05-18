#pragma once

#include "core.h"

class OnkyoAmp {

  private:

    bool _on;
    int _current;

  public:

    void dvr() {
      on();
      if (_current != 1) {
        // Send Onkyo Input DVR
        _current = 1;
      }
    }

    void cable() {
      on();
      if (_current != 2) {
        // Send Onkyo Input CBL
        _current = 2;
      }
    }

    void game() {
      on();
      if (_current != 3) {
        // Send Onkyo Input Game
        _current = 3;
      }
    }

    void aux() {
      on();
      if (_current != 4) {
        // Send Onkyo input AUX
        _current = 4;
      }
    }

    void multiChannel() {
      on();
      if (_current != 5) {
        // Send Onkyo input MultiChannel
        _current = 5;
      }
    }

    void dvd() {
      on();
      if (_current != 6) {
        // Send Onkyo input DVD
        _current = 6;
      }
    }

    void tape() {
      on();
      if (_current != 7) {
        // Send Onkyo input Tape
        _current = 7;
      }
    }

    void tuner() {
      on();
      if (_current != 8) {
        // Send Onkyo input Tuner
        _current = 8;
      }
    }

    void off() {
      // Send OnkyoPowerOff
      _on = false;
    }

  private:

    void on() {
      if (!_on) {
        // Send OnkyoPowerOn
        _on = true;
      }
    }

};

/*  
== Onkyo ==
Vol+: NEC: 4BB640BF (32 bits)
  repeat (same)
Vol-: NEC: 4BB6C03F (32 bits)
  repeat (same)
PowerOn: NEC: 4BB620DF (32 bits)
PowerOff: NEC: d(32 bits)
InputVCR/DVR: NEC: 4BB6F00F (32 bits)
InputCBL/SAT: NEC: 4BB6708F (32 bits)
InputGAME/TV: NEC: 4BB6B04F (32 bits)
InputAUX: NEC: 4BB6F906 (32 bits)
InputMulitCH: NEC: 4B3620DF (32 bits)
InputDVD: NEC: 4B3631CE (32 bits)
InputTape: NEC: 4BB610EF (32 bits)
InputTuner: NEC: 4BB6D02F (32 bits)
InputCD: NEC: 4BB6906F (32 bits) 
MuteOn: NEC: 4B3621DE (32 bits)
MuteOff: NEC: 4B36A15E (32 bits)
Listen>: NEC: 4BB632CD (32 bits)
Listen<: NEC: 4B36A25D (32 bits)
ListenStereo: NEC: 4B3632CD (32 bits)
ListenSurround: NEC: 4B36B24D (32 bits)
ListenPureAudio: NEC: 4B36CB34 (32 bits)
ListenDTS: NEC: 4B368B74 (32 bits)
ListenDolby: NEC: 4B360BF4 (32 bits)
ListenDirect: NEC: 4BB622DD (32 bits)
ListenAllChStereo: NEC: 4B364AB5 (32 bits)
*/
