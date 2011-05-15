#include <Arduino.h>

int led = HIGH;

void setup() {
	Serial.begin(BAUD);
  Serial.println("Hello...");
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, led);

  if (Serial.available() > 0) { // on serial data

    // toggle led
    led = led == HIGH ? LOW : HIGH;
    digitalWrite(13, led);

    // echo result
    int b = Serial.read();
    Serial.print("got: ");
    Serial.println(b, DEC);
  }
}
