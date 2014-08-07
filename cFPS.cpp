#include "cFPS.h"

cFPS cFPS::FPSControl;

cFPS::cFPS() {
	_oldTime = 0;
	_lastTime = 0;
	_speedFactor = 0.0f;
	_numFrames = 0;
	_frames = 0;
}

///<summary>Updates the frames per second and speed factor.</summary>
void cFPS::Update() {
	if (_oldTime + 1000 < SDL_GetTicks()) {
		_oldTime = SDL_GetTicks();
		_numFrames = _frames;
		_frames = 0;
	}

	_speedFactor = (float)(((SDL_GetTicks() - _lastTime) / 1000.0f) * 30.0f);
	_lastTime = SDL_GetTicks();
	_frames++;
}

///<summary>Get the number of frames per second.</summary>
///<returns>Returns the frames per second.</returns>
int cFPS::GetFPS() {
	return _numFrames;
}

///<summary>Get the speed factor of the computer.</summary>
///<returns>Returns the speed factor.</returns>
float cFPS::GetSpeedFactor() {
	return _speedFactor;
}

//
// TODO: Include function to display the FPS on the screen.
//