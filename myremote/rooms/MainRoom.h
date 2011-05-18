#pragma once

#include "equipment/comcast.h"
#include "equipment/denon-dvd.h"
#include "equipment/onkyo-amp.h"
#include "equipment/panasonic-tv.h"
#include "equipment/roku.h"

class MainRoom {

  private:

    OnkyoAmp amp;
    PanasonicTv tv;
    DenonDvd dvd;
    Comcast comcast;
    RokuStreamer roku;

  public:

    void watchComcast() {
      amp.cable();
      tv.input(4);
      dvd.off();
      comcast.on();
    }

    void watchDvd() {
      amp.dvd();
      tv.input(4);
      dvd.on();
      comcast.off();
    }

    void streamRoku() {
      amp.dvr();
      tv.input(4);
      dvd.off();
      comcast.off();
    }

    void playPlaystation() {
      amp.game();
      tv.input(4);
      dvd.off();
      comcast.off();
    }

    void listenCd() {
      amp.dvd();
      tv.off();
      dvd.on();
      comcast.off();
    }

    void allOff() {
      amp.off();
      tv.off();
      dvd.off();
      comcast.off();
    }

};

