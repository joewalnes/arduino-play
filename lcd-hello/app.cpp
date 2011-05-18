// From http://www.arduino.cc/playground/Learning/SparkFunSerLCD

#include <Arduino.h>

#include <NewSoftSerial.h>

NewSoftSerial LCD(0,2);

void selectLineOne(){  //puts the cursor at line 0 char 0.
   LCD.print(0xFE, BYTE);   //command flag
   LCD.print(128, BYTE);    //position
   delay(10);
}
void selectLineTwo(){  //puts the cursor at line 0 char 0.
   LCD.print(0xFE, BYTE);   //command flag
   LCD.print(192, BYTE);    //position
   delay(10);
}
void goTo(int position) { //position = line 1: 0-15, line 2: 16-31, 31+ defaults back to 0
if (position<16){ LCD.print(0xFE, BYTE);   //command flag
              LCD.print((position+128), BYTE);    //position
}else if (position<32){LCD.print(0xFE, BYTE);   //command flag
              LCD.print((position+48+128), BYTE);    //position 
} else { goTo(0); }
   delay(10);
}

void clearLCD(){
   LCD.print(0xFE, BYTE);   //command flag
   LCD.print(0x01, BYTE);   //clear command.
   delay(10);
}
void backlightOn(){  //turns on the backlight
    LCD.print(0x7C, BYTE);   //command flag for backlight stuff
    LCD.print(157, BYTE);    //light level.
   delay(10);
}
void backlightOff(){  //turns off the backlight
    LCD.print(0x7C, BYTE);   //command flag for backlight stuff
    LCD.print(128, BYTE);     //light level for off.
   delay(10);
}
void serCommand(){   //a general function to call the command flag for issuing all other commands   
  LCD.print(0xFE, BYTE);
}

void setup()
{
  LCD.begin(9600);
  backlightOn();
}

void loop()
{  
  selectLineOne();
  LCD.print(millis());
  selectLineTwo();
  LCD.print(millis()/2);
  delay(100);
}

