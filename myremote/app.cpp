#include <Arduino.h>
#include <IRremote.h>

#include "rooms/MainRoom.h"

IRsend irsend;
MainRoom room;

void setup() {
  Serial.begin(BAUD);
}

void loop() {
  switch (Serial.read()) {
    case 'c': room.watchComcast(); break;
    case 'd': room.watchDvd(); break;
    case 'r': room.streamRoku(); break;
    case 'p': room.playPlaystation(); break;
    case 'l': room.listenCd(); break;
    case 'o': room.allOff(); break;
  }
}
