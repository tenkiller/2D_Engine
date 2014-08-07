#include "cMap.h"

//cMap cMap::mapControl;

cMap::cMap() {
	tileSet = 0;
}

cMap::~cMap() {
	_tileList.clear();
}

///<summary>Loads the list of tiles from a tileset that belong to this map.</summary>
///<param name="file">The file location of the map data.</param>
///<returns>True is the map is loaded; false otherwise.</returns>
///<remarks>The tileset surface must be set linked to the map via its member variable.</remarks>
bool cMap::Load(char *file) {
	if (file == 0) return false;

	_tileList.clear();

	FILE* fileHandle;
	int err;

	// open the file for reading
	if ((err = fopen_s(&fileHandle, file, "r")) != 0) return false;
	// ensure we have a handle to the file
	//if (fileHandle == 0) return false;

	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			cTile tempTile;

			fscanf_s(fileHandle, "%d:%d ", &tempTile.tileID, &tempTile.typeID);
			// put the tile in the map's tile list
			_tileList.push_back(tempTile);
		}
		fscanf_s(fileHandle, "\n");
	}

	fclose(fileHandle);

	return true;
}

///<summary>Renders the map onto an SDL surface at the given coordinates.</summary>
///<param name="dest">The destination surface to render the map onto.</param>
///<param name="mapX">The x-coordinate in the destination surface to render the map onto.</param>
///<param name="mapY">The y-coordinate in the destination surface to render the map onto.</param>
void cMap::Render(SDL_Surface* dest, int mapX, int mapY) {
	if (dest == 0) return;

	int numTiles = tileSet->w / TILE_SIZE;
	int id = 0;

	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			if (_tileList[id].typeID == TILE_TYPE_NONE) {
				id++;
				continue;
			}

			// determine the coordinates to draw the tile on the destination surface
			int destX = mapX + (x * TILE_SIZE);
			int destY = mapY + (y * TILE_SIZE);
			// determine the coordinates to grab the right tile from the tileset
			int tX = (_tileList[id].tileID % numTiles) * TILE_SIZE;
			int tY = (_tileList[id].tileID / numTiles) * TILE_SIZE;
			
			// draw the tile
			cSurface::Draw(dest, tileSet, destX, destY, tX, tY, TILE_SIZE, TILE_SIZE);
			id++;
		}
	}
}

///<summary>Get the tile that contains the given coordinates.</summary>
///<param name="x">The x-coordinate, in pixels.</param>
///<param name="y">The y-coordinate, in pixels.</param>
///<returns>Returns the tile found at those coordinates, or null if not found.</returns>
cTile* cMap::GetTile(int x, int y) {
	unsigned int id = ((y / TILE_SIZE) * MAP_WIDTH) + (x / TILE_SIZE);

	if (id < 0 || id >= _tileList.size()) return 0;

	return &_tileList[id];
}