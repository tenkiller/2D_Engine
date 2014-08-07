#ifndef _CSCREENMANAGER_H_
#define _CSCREENMANAGER_H_

#include <vector>

#include "cScreen.h"

class cScreenManager {
public:
	cScreenManager(SDL_Surface* main);
	~cScreenManager();
	bool Push(cScreen* screen);
	void Pop();
	void Clear();
	void Update();
	void Render();
	void OnEvent(SDL_Event* Event);
	
private:
	SDL_Surface* _videoSurface;
	std::vector<cScreen*> _gameScreens;
};

#endif