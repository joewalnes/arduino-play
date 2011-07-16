/*
	HughesyShiftBrite.h - A library to run shiftbrites
	Created by Ashley J. Hughes, 14 Jun 2010.
	ashley.hughes@me.com
	Based on a post found @ http://macetech.com/blog/node/54
*/

#ifndef HughesyShiftBrite_h
#define HughesyShiftBrite_h

#include "WProgram.h"

class HughesyShiftBrite
{
public:
	HughesyShiftBrite();
	HughesyShiftBrite(int dataPin, int latchPin, int enablePin, int clockPin);
	void sendColour(int r, int g, int b);
private:
	int _SB_CommandMode;
	int _SB_RedCommand;
	int _SB_GreenCommand;
	int _SB_BlueCommand;
	int _dPin;
	int _lPin;
	int _ePin;
	int _cPin;
	unsigned long _SB_CommandPacket;
	void _SB_SendPacket();
};

#endif