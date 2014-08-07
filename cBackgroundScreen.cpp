#include "cBackgroundScreen.h"

cBackgroundScreen::cBackgroundScreen() {
}

bool cBackgroundScreen::Load() {
	return true;
}

void cBackgroundScreen::Update() {
}

void cBackgroundScreen::Render(SDL_Surface* dest) {
	if (dest == 0) return;

	SDL_FillRect(dest, 0, 0);
}