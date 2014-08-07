#include "cApp.h"

///<summary>Updates all entities on the game screen.</summary>
void cApp::Update() {
	_screenManager->Update();

	// update the frames per second counter
	cFPS::FPSControl.Update();
}