#ifndef _CSURFACE_H_
#define _CSURFACE_H_

#include "SDL.h"

class cSurface {
public:
	cSurface();
	static SDL_Surface* LoadFromFile(char* file);
	static bool Draw(SDL_Surface* dest, SDL_Surface* src, int x, int y);
	static bool Draw(SDL_Surface* dest, SDL_Surface* src, int destX, int destY, int srcX, int srcY, int w, int h);
	static bool Transparent(SDL_Surface* dest, int r, int g, int b);
};

#endif