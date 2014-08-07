#ifndef _CSCREEN_H_
#define _CSCREEN_H_

#include <vector>

#include "SDL.h"
#include "cEvent.h"
#include "cEntity.h"

class cScreenManager;

class cScreen : public cEvent {
public:
	cScreen();
	virtual ~cScreen();
	virtual bool Load() = 0;
	virtual void Update() = 0;
	virtual void Render(SDL_Surface* dest) = 0;
	virtual void UnLoad();

	void SetScreenManager(cScreenManager* screenManager);
	int AddSurface(char* file);
	//bool AddEntity(char* file, int w, int h, int frames);

	bool active;

protected:
	bool _exiting;
	bool _popup;
	bool _covered;
	int _transitionOnTime;
	int _transitionOffTime;

	cScreenManager* _screenManager;
	std::vector<SDL_Surface*> _surfaceList;
};

#endif