#pragma once

#include "control/infrared.h"

class OnkyoAmp {

  private:

    enum Input { OFF, DVR, CABLE, GAME, AUX,
                 MULTICH, DVD, TAPE, TUNER, CD } _current;

    bool _muted;

  public:

    OnkyoAmp() : _current(OFF), _muted(false) {}

    void dvr() {
      switchInput(DVR);
    }

    void cable() {
      switchInput(CABLE);
    }

    void game() {
      switchInput(GAME);
    }

    void aux() {
      switchInput(AUX);
    }

    void multiChannel() {
      switchInput(MULTICH);
    }

    void dvd() {
      switchInput(DVD);
    }

    void tape() {
      switchInput(TAPE);
    }

    void tuner() {
      switchInput(TUNER);
    }

    void cd() {
      switchInput(CD);
    }

    void off() {
      // TODO: ir.send(ir.nec(0xXXX)); // PowerOff
      _current = OFF;
    }

    void mute() {
      if (!_muted) {
        ir.send(ir.nec(0x4B3621DE)); // MuteOn
        _muted = true;
      }
    }

    void unmute() {
      if (_muted) {
        ir.send(ir.nec(0x4B36A15E)); // MuteOff
        _muted = false;
      }
    }

    void alterVolum(int amount) {
      for (int i = 0; i < abs(amount); i++) {
        ir.send(ir.nec(amount > 0 ? 0x4BB640BF : 0x4BB6C03F)); // VolumeUp/Down
      }
    }

  private:

    void switchInput(Input input) {
      if (_current == OFF) {
        ir.send(ir.nec(0x4BB620DF)); // PowerOn
      }
      if (_current != input) {
        switch (input) {
          case DVR:     ir.send(ir.nec(0x4BB6F00F)); break; // InputDVR
          case CABLE:   ir.send(ir.nec(0x4BB6708F)); break; // InputCable
          case GAME:    ir.send(ir.nec(0x4BB6B04F)); break; // InputGame
          case AUX:     ir.send(ir.nec(0x4BB6F906)); break; // InputAux
          case MULTICH: ir.send(ir.nec(0x4B3620DF)); break; // InputMultichannel
          case DVD:     ir.send(ir.nec(0x4B3631CE)); break; // InputDvd
          case TAPE:    ir.send(ir.nec(0x4BB610EF)); break; // InputTape
          case TUNER:   ir.send(ir.nec(0x4BB6D02F)); break; // InputTuner
          case CD:      ir.send(ir.nec(0x4BB6906F)); break; // InputCD
        }
        _current = input;
      }
    }

};

/*  
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
