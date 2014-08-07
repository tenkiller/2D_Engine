#ifndef _CFPS_H_
#define _CFPS_H_

#define FRAME_RATE 32.0

#include "SDL.h"

class cFPS {
public:
	cFPS();
	void Update();
	int GetFPS();
	float GetSpeedFactor();

private:
	unsigned int _oldTime;
	unsigned int _lastTime;
	float _speedFactor;
	int _numFrames;
	int _frames;

public:
	static cFPS FPSControl;
};

#endif