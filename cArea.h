#ifndef _CAREA_H_
#define _CAREA_H_

#include "cMap.h"

class cArea {
public:
	cArea();
	bool Load(char* file);
	void Render(SDL_Surface* dest, int cameraX, int cameraY);
	void UnLoad();
	cMap* GetMap(int x, int y);
	cTile* GetTile(int x, int y);

private:
	int _areaWidth;
	int _areaHeight;
	SDL_Surface* _tileSet;
	static const int _mapPixelWidth = MAP_WIDTH * TILE_SIZE;
	static const int _mapPixelHeight = MAP_HEIGHT * TILE_SIZE;

public:
	std::vector<cMap> mapList;
	static cArea areaControl;
};

#endif