#include "cApp.h"

///<summary>Renders all entities to the game screen.</summary>
void cApp::Render() {
	_screenManager->Render();

	SDL_Flip(_screen);
}