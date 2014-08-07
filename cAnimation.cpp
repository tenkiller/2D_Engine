#include "cAnimation.h"

cAnimation::cAnimation() {
	_currentFrame = 0;
	_oldTime = 0;
	maxFrames = 0;
	frameRate = 100;	// milliseconds
}

///<summary>Runs the animation through each frame, based on the frame rate.</summary>
void cAnimation::Animate() {
	if ((Uint32)(_oldTime + frameRate) > SDL_GetTicks()) return;

	_oldTime = SDL_GetTicks();

	if (_currentFrame++ >= maxFrames - 1) _currentFrame = 0;
}

///<summary>Gets the current frame in the animation.</summary>
///<returns>The current frame number.</returns>
int cAnimation::GetCurrentFrame() {
	return _currentFrame;
}

///<summary>Sets the current frame in the animation.</summary>
///<param name="frame">The frame number.</param>
void cAnimation::JumpToFrame(int frame) {
	_currentFrame = frame;
}