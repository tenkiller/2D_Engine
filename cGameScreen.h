#ifndef _CGAMESCREEN_H_
#define _CGAMESCREEN_H_

#include "cScreen.h"
#include "cPlayer.h"
#include "cArea.h"
#include "cCamera.h"

class cGameScreen : public cScreen {
public:
	cGameScreen();
	bool Load();
	void Update();
	void Render(SDL_Surface* dest);
	void UnLoad();
	void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

private:
	cPlayer _yoshi;
	cEntity _yoshiclone;
};

#endif