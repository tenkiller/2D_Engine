#include "cScreen.h"

class cBackgroundScreen : public cScreen {
public:
	cBackgroundScreen();
	bool Load();
	void Update();
	void Render(SDL_Surface* dest);
};