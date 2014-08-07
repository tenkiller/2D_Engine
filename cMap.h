#ifndef _CMAP_H_
#define _CMAP_H_

#include <vector>

#include "SDL.h"
#include "globals.h"
#include "cTile.h"
#include "cSurface.h"

class cMap {
public:
	cMap();
	~cMap();
	bool Load(char* file);
	void Render(SDL_Surface* dest, int mapX, int mapY);
	cTile* GetTile(int x, int y);

public:
	SDL_Surface* tileSet;	// the tileset graphic for this map
	//static cMap mapControl;

private:
	std::vector<cTile> _tileList;
};

#endif