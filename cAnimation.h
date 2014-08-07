#ifndef _CANIMATION_H_
#define _CANIMATION_H_

#include <SDL.h>

class cAnimation {
public:
	cAnimation();
	void Animate();
	int GetCurrentFrame();
	void JumpToFrame(int frame);

	int frameRate;
	int maxFrames;

private:
	int _currentFrame;
	int _oldTime;
};

#endif