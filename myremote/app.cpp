#include <Arduino.h>
#include <CmdMessenger.h>

#include "rooms/MainRoom.h"

CmdMessenger cmdMessenger = CmdMessenger(Serial, ' ', ';');

MainRoom room;

enum Cmds {
  ACK      = 1,
  PING     = 2,
  ACTIVITY = 3,
  RESET    = 4
};

void ping() {
  cmdMessenger.sendCmd(ACK, "Ping");
}

void changeActivity() {
  char activity = cmdMessenger.readChar();
  switch (activity) {
    case 'c': room.watchComcast(); break;
    case 'd': room.watchDvd(); break;
    case 'r': room.streamRoku(); break;
    case 'p': room.playPlaystation(); break;
    case 'l': room.listenCd(); break;
    case 'o': room.allOff(); break;
    default: return;
  }
  cmdMessenger.sendCmd(ACK, "Activity"); //"" << activity);
}

void forceReset() {
  room.forceReset();
  cmdMessenger.sendCmd(ACK, "Reset");
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

