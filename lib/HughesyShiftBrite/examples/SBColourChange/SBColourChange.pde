#include "HughesyShiftBrite.h"

HughesyShiftBrite sb;

void setup()
{
  // sb = HughesyShiftBrite(); 
  sb = HughesyShiftBrite(10,11,12,13);
}

void loop()
{
  sb.sendColour(0,0,1023);
  delay(5000);
  sb.sendColour(0,1023,0);
  delay(5000);
  sb.sendColour(1023,0,0);
  delay(5000);
}

