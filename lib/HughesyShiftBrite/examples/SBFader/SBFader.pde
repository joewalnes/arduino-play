#include "HughesyShiftBrite.h"
HughesyShiftBrite sb;

int maxVal = 1023;
const int DELAY_VAL = 25;

void setup()
{
  sb = HughesyShiftBrite();

}

void loop()
{
  for (int i = 0; i <= maxVal; i++)
  {
    sb.sendColour(i,0,0);
    delay(DELAY_VAL);
  }
  for (int i = maxVal; i > 0; i--)
  {
    sb.sendColour(i,0,0);
    delay(DELAY_VAL);
  }
  for (int i = 0; i <= maxVal; i++)
  {
    sb.sendColour(0,i,0);
    delay(DELAY_VAL);
    Serial.println(i);
  }
  for (int i = maxVal; i > 0; i--)
  {
    sb.sendColour(0,i,0);
    delay(DELAY_VAL);
  }
  for (int i = 0; i <= maxVal; i++)
  {
    sb.sendColour(0,0,i);
    delay(DELAY_VAL);
  }
  for (int i = maxVal; i > 0; i--)
  {
    sb.sendColour(0,0,i);
    delay(DELAY_VAL);
  }
  for (int i = 0; i <= maxVal; i++)
  {
    sb.sendColour(i,i,0);
    delay(DELAY_VAL);
    Serial.println(i);
  }
  for (int i = maxVal; i > 0; i--)
  {
    sb.sendColour(i,i,0);
    delay(DELAY_VAL);
  }
  for (int i = 0; i <= maxVal; i++)
  {
    sb.sendColour(i,0,i);
    delay(DELAY_VAL);
  }
  for (int i = maxVal; i > 0; i--)
  {
    sb.sendColour(i,0,i);
    delay(DELAY_VAL);
  }
  for (int i = 0; i <= maxVal; i++)
  {
    sb.sendColour(0,i,i);
    delay(DELAY_VAL);
    Serial.println(i);
  }
  for (int i = maxVal; i > 0; i--)
  {
    sb.sendColour(0,i,i);
    delay(DELAY_VAL);
  }
  for (int i = 0; i <= maxVal; i++)
  {
    sb.sendColour(i,i,i);
    delay(DELAY_VAL);
  }
  for (int i = maxVal; i > 0; i--)
  {
    sb.sendColour(i,i,i);
    delay(DELAY_VAL);
  }
}




