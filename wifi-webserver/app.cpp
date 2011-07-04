/*
 * Web Server
 *
 * A simple web server example using the WiShield 1.0
 */
#include <Arduino.h>
#include <WiShield.h>

#include "wifi-settings.h"

void setup()
{
	WiFi.init();
}

// This is the webpage that is served up by the webserver
const prog_char webpage[] PROGMEM = {"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<center><h1>Hello World!! I am WiShield</h1><form method=\"get\" action=\"0\">Toggle LED:<input type=\"submit\" name=\"0\" value=\"LED1\"></input></form></center>"};

void loop()
{
	WiFi.run();
}
