#include "cScreen.h"

cScreen::cScreen() {
	active = false;
	_exiting = false;
	_popup = false;
	_covered = false;
	_transitionOnTime = 0;
	_transitionOffTime = 0;
	_screenManager = 0;
}

cScreen::~cScreen() {
	UnLoad();
}

void cScreen::UnLoad() {
	if (!_surfaceList.empty()) {
		std::vector<SDL_Surface*>::iterator iter;

		for (iter = _surfaceList.begin(); iter != _surfaceList.end(); iter++) {
			SDL_FreeSurface((*iter));
			(*iter) = 0;
		}
		_surfaceList.clear();
	}
	
	/*if (!_entityList.empty()) {
		std::vector<cEntity*>::iterator iter;

		for (iter = _entityList.begin(); iter != _entityList.end(); iter++) {
			(*iter)->UnLoad();
			(*iter) = 0;
		}
		_entityList.clear();
	}*/
}

void cScreen::SetScreenManager(cScreenManager* screenManager) {
	if (screenManager == 0) return;

	_screenManager = screenManager;
}

int cScreen::AddSurface(char* file) {
	if (file == 0) return -1;

	SDL_Surface* newSurface = 0;
	if ((newSurface = cSurface::LoadFromFile(file)) == 0) return -1;
	
	cSurface::Transparent(newSurface, 255, 0, 255);

	_surfaceList.push_back(newSurface);

	return (int)(_surfaceList.size()-1);
}

//bool cScreen::AddEntity(char* file, int w, int h, int frames) {
//	if (file == 0) return false;
//
//	cEntity* newEntity = 0;
//	if ((newEntity = new cEntity()) == 0) return false;
//	if ((newEntity->Load(file, w, h, frames)) == false) return false;
//
//	_entityList.push_back(newEntity);
//
//	return true;
//}