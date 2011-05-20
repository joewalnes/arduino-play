#include <Arduino.h>
#include <CmdMessenger.h>

#include "rooms/MainRoom.h"

CmdMessenger cmdMessenger = CmdMessenger(Serial, ' ', ';');

MainRoom room;

enum Cmds {
  PING     = 0,
  PONG     = 1,
  ACTIVITY = 10,
  RESET    = 11
};

void ping() {
  cmdMessenger.sendCmd(PONG, "");
}

void changeActivity() {
  switch (cmdMessenger.readChar()) {
    case 'c': room.watchComcast(); break;
    case 'd': room.watchDvd(); break;
    case 'r': room.streamRoku(); break;
    case 'p': room.playPlaystation(); break;
    case 'l': room.listenCd(); break;
    case 'o': room.allOff(); break;
  }
}

void forceReset() {
  room.forceReset();
}

void setup() {
  Serial.begin(BAUD);
  cmdMessenger.attach(PING, ping);
  cmdMessenger.attach(ACTIVITY, changeActivity);
  cmdMessenger.attach(RESET, forceReset);
}

void loop() {
  cmdMessenger.feedinSerialData();
}

