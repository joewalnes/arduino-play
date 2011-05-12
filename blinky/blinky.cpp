#include <WProgram.h>

extern "C" void __cxa_pure_virtual(void) {
    while(1);
} 

int led = HIGH;

void setup() {
	Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, (millis() / 500) % 2 ? HIGH : LOW);

  if (Serial.available() > 0) {
    led = led == HIGH ? LOW : HIGH;
    //digitalWrite(13, led);
    int b = Serial.read();
    Serial.print("got: ");
    Serial.println(b, DEC);
  }
}
