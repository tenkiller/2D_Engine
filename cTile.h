#ifndef _CTILE_H_
#define _CTILE_H_

enum eTileType {
	TILE_TYPE_NONE = 0,
	TILE_TYPE_NORMAL,
	TILE_TYPE_BLOCK,
	TILE_TYPE_PAIN
};

class cTile {
public:
	cTile();

	int tileID;
	int typeID;
};

#endif