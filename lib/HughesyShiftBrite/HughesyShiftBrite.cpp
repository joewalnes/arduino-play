/*
	HughesyShiftBrite.cpp - A library to run shiftbrites
	Created by Ashley J. Hughes, 14 Jun 2010.
	ashley.hughes@me.com
	Based on a post found @ http://macetech.com/blog/node/54
*/

#include "WProgram.h"
#include "HughesyShiftBrite.h"

HughesyShiftBrite::HughesyShiftBrite()
{
	HughesyShiftBrite(10,11,12,13);
}

HughesyShiftBrite::HughesyShiftBrite(int dataPin, int latchPin, int enablePin, int clockPin)
{
	_dPin = dataPin;
	_lPin = latchPin;
	_ePin = enablePin;
	_cPin = clockPin;
	
	pinMode(_dPin, OUTPUT);
	pinMode(_lPin, OUTPUT);
	pinMode(_ePin, OUTPUT);
	pinMode(_cPin, OUTPUT);
	
	digitalWrite(_lPin, LOW);
	digitalWrite(_ePin, LOW);
}

void HughesyShiftBrite::sendColour(int r, int g, int b)
{
	if (r <= 1023 && g <= 1023 && b <= 1023) 
	{
		_SB_CommandMode = B00;
		_SB_RedCommand = r;
		_SB_GreenCommand = g;
		_SB_BlueCommand = b;
		_SB_SendPacket();
	}
	else
	{
		//FLASH RED 7 times for error
		_SB_CommandMode = B00;
		_SB_RedCommand = 0;
		_SB_GreenCommand = 0;
		_SB_BlueCommand = 0;
		_SB_SendPacket();
		
		for(int i = 0; i < 7; i++)
		{
			delay(100);
			_SB_RedCommand = 1023;
			_SB_SendPacket();
			delay(100);
			_SB_RedCommand = 0;
			_SB_SendPacket();
		}
	}
}

void HughesyShiftBrite::_SB_SendPacket() 
{
  _SB_CommandPacket = _SB_CommandMode & B11;
  _SB_CommandPacket = (_SB_CommandPacket << 10)  | (_SB_BlueCommand & 1023);
  _SB_CommandPacket = (_SB_CommandPacket << 10)  | (_SB_RedCommand & 1023);
  _SB_CommandPacket = (_SB_CommandPacket << 10)  | (_SB_GreenCommand & 1023);

  shiftOut(_dPin, _cPin, MSBFIRST, _SB_CommandPacket >> 24);
  shiftOut(_dPin, _cPin, MSBFIRST, _SB_CommandPacket >> 16);
  shiftOut(_dPin, _cPin, MSBFIRST, _SB_CommandPacket >> 8);
  shiftOut(_dPin, _cPin, MSBFIRST, _SB_CommandPacket);

  delay(1);
  digitalWrite(_lPin,HIGH);
  delay(1);
  digitalWrite(_lPin,LOW);
}
