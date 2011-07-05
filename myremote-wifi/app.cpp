#include <Arduino.h>
#include <WiShield.h>

extern "C" {
#include "uip.h"
#include <string.h>
#include "webserver.h"
#include "config.h"
}

#include "wifi-settings.h"
#include "rooms/MainRoom.h"

#define SPACE 0x20

#define RESPOND_STR(s, str) PSOCK_SEND(&s->p, (unsigned char*)str, strlen(str));
#define RESPOND_DATA(s, data, len) PSOCK_SEND(&s->p, (unsigned char*)data, len);
#define STR_EQ(input, str) (strncmp(input, (str), strlen(str)) == 0)

MainRoom room;

int n = 0;

int handle_connection(webserver_state* s) {
	PSOCK_BEGIN(&s->p);

	// Read HTTP verb (e.g. GET/POST) - and ignore it.
	PSOCK_READTO(&s->p, ' ');
	// Read requested path (up to next space)
	PSOCK_READTO(&s->p, ' ');

  RESPOND_STR(s, "HTTP/1.1 200 OK\r\n");
  RESPOND_STR(s, "Content-Type: text/plain\r\n");
  RESPOND_STR(s, "\r\n");

  if (STR_EQ(s->inputbuf, "/ ")) {
    // no-op, just for testing
    RESPOND_STR(s, "test");
  } else if (STR_EQ(s->inputbuf, "/comcast ")) {
    room.watchComcast();
    RESPOND_STR(s, "comcast");
  } else if (STR_EQ(s->inputbuf, "/dvd ")) {
    room.watchDvd();
    RESPOND_STR(s, "dvd");
  } else if (STR_EQ(s->inputbuf, "/roku ")) {
    room.streamRoku();
    RESPOND_STR(s, "roku");
  } else if (STR_EQ(s->inputbuf, "/ps3 ")) {
    room.playPlaystation();
    RESPOND_STR(s, "ps3");
  } else if (STR_EQ(s->inputbuf, "/cd ")) {
    room.listenCd();
    RESPOND_STR(s, "cd");
  } else if (STR_EQ(s->inputbuf, "/off ")) {
    room.allOff();
    RESPOND_STR(s, "off");
  } else if (STR_EQ(s->inputbuf, "/reset ")) {
    room.forceReset();
    RESPOND_STR(s, "reset");
  } else {
    RESPOND_STR(s, "unknown");
  }

  RESPOND_STR(s, "\r\n");
  PSOCK_CLOSE(&s->p);
  PSOCK_END(&s->p);
}

void setup() {
	WiFi.init();
}

void loop() {
	WiFi.run();
}

extern "C" {

void webserver_init() {
	uip_listen(HTONS(80));
}

void webserver_appcall() {
	webserver_state* s = &(uip_conn->appstate);

	if(uip_connected()) {
		PSOCK_INIT(&s->p, (unsigned char*)s->inputbuf, sizeof(s->inputbuf));
	}

	handle_connection(s);
}

} // extern "C"

