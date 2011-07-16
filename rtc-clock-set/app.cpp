#include <Arduino.h>
#include "Wire.h"
#define DS1307_ADDRESS 0x68

/**
 * Used to set time on DS1307 Real Time Clock module
 * <http://www.sparkfun.com/products/99>
 *
 * From this tutorial: http://bildr.org/2011/03/ds1307-arduino/
 *
 * Arduino -> Module
 * -----------------
 * 5V -> 5V
 * Gnd -> Gnd
 * A4 -> SDA
 * A5 -> SCL
 */

void setDateTime();
void printDate();
byte decToBcd(byte val);

void setup(){
  Wire.begin();
  Serial.begin(BAUD);
  setDateTime(); //MUST CONFIGURE IN FUNCTION
}

void loop(){
  printDate();
  delay(1000);
}

void setDateTime(){

  byte second =      0; //0-59
  byte minute =      40; //0-59
  byte hour =        16; //0-23
  byte weekDay =     7; //1-7
  byte monthDay =    16; //1-31
  byte month =       7; //1-12
  byte year  =       11; //0-99

  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.send(0); //stop Oscillator

  Wire.send(decToBcd(second));
  Wire.send(decToBcd(minute));
  Wire.send(decToBcd(hour));
  Wire.send(decToBcd(weekDay));
  Wire.send(decToBcd(monthDay));
  Wire.send(decToBcd(month));
  Wire.send(decToBcd(year));

  Wire.send(0); //start 

  Wire.endTransmission();

}

byte decToBcd(byte val){
// Convert normal decimal numbers to binary coded decimal
  return ( (val/10*16) + (val%10) );
}

byte bcdToDec(byte val)  {
// Convert binary coded decimal to normal decimal numbers
  return ( (val/16*10) + (val%16) );
}

void printDate(){

  // Reset the register pointer
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.send(0);
  Wire.endTransmission();

  Wire.requestFrom(DS1307_ADDRESS, 7);

  int second = bcdToDec(Wire.receive());
  int minute = bcdToDec(Wire.receive());
  int hour = bcdToDec(Wire.receive() & 0b111111); //24 hour time
  int weekDay = bcdToDec(Wire.receive()); //0-6 -> sunday - Saturday
  int monthDay = bcdToDec(Wire.receive());
  int month = bcdToDec(Wire.receive());
  int year = bcdToDec(Wire.receive());

  //print the date EG   3/1/11 23:59:59
  Serial.print(month);
  Serial.print("/");
  Serial.print(monthDay);
  Serial.print("/");
  Serial.print(year);
  Serial.print(" ");
  Serial.print(hour);
  Serial.print(":");
  Serial.print(minute);
  Serial.print(":");
  Serial.println(second);

}
