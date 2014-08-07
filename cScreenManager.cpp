#include "cScreenManager.h"

///<summary>Constructor.</summary>
///<param name="main">The SDL surface that all screens will draw to.</param>
cScreenManager::cScreenManager(SDL_Surface* main) {
	if (main == 0) _videoSurface = 0;

	_videoSurface = main;
}

cScreenManager::~cScreenManager() {
	while (!_gameScreens.empty()) {	Pop(); }
}

///<summary>Pushes a screen object onto the stack.</summary>
///<param name="screen">A pointer to a screen object.</param>
///<returns>True if the operation is successful; false otherwise.</returns>
bool cScreenManager::Push(cScreen* screen) {
	if (screen == 0) return false;

	// load all the screen's resources
	screen->Load();
	// push it onto the stack
	_gameScreens.push_back(screen);

	return true;
}

///<summary>Pops a screen off of the stack and frees the resources its using.</summary>
void cScreenManager::Pop() {
	// free memory of screen's resources
	_gameScreens.back()->UnLoad();
	// pop the screen off the stack
	_gameScreens.pop_back();
}

///<summary>Clears the stack of all screen objects and the resources they use.</summary>
void cScreenManager::Clear() {
	std::vector<cScreen*>::iterator iter;

	for (iter = _gameScreens.begin(); iter != _gameScreens.end(); iter++) {
		(*iter)->UnLoad();
	}

	_gameScreens.clear();
}

///<summary>Updates the active screen(s).</summary>
void cScreenManager::Update() {
	std::vector<cScreen*>::iterator iter;

	for (iter = _gameScreens.begin(); iter != _gameScreens.end(); iter++) {
		if ((*iter)->active) (*iter)->Update();
	}
}

///<summary>Renders all screens on the stack to the main SDL surface.</summary>
void cScreenManager::Render() {
	std::vector<cScreen*>::iterator iter;

	for (iter = _gameScreens.begin(); iter != _gameScreens.end(); iter++) {
		(*iter)->Render(_videoSurface);
	}
}

///<summary>Passes all events to the top screen on the stack.</summary>
void cScreenManager::OnEvent(SDL_Event* Event) {
	_gameScreens.back()->OnEvent(Event);
}