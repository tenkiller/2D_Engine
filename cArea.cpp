#include "cArea.h"

cArea cArea::areaControl;

cArea::cArea() {
	_tileSet = 0;
	_areaWidth = 0;
	_areaHeight = 0;
}

///<summary>Loads the area's maps and associated tile set.</summary>
///<param name="file">The file containing the formatted area and map data.</param>
///<returns>True if the area was loaded; false otherwise.</returns>
///<remarks>
/// The file is formatted as follows:
/// ./tileset/tileset.png
/// 3
/// ./maps/1.map ./maps/2.map ./maps/3.map
/// ...
///</remarks>
bool cArea::Load(char *file) {
	if (file == 0) return false;

	mapList.clear();

	FILE* fileHandle;
	int err;

	// open the file for reading
	if ((err = fopen_s(&fileHandle, file, "r")) != 0) return false;

	char tileSetFile[255];
	// get the path to the tileset file
	fscanf_s(fileHandle, "%s\n", tileSetFile, 255);

	// load the tileset
	if ((_tileSet = cSurface::LoadFromFile(tileSetFile)) == false) {
		fclose(fileHandle);
		return false;
	}

	cSurface::Transparent(_tileSet, 255, 0, 255);

	// get the size of the area
	fscanf_s(fileHandle, "%d\n", &_areaWidth);
	fscanf_s(fileHandle, "%d\n", &_areaHeight);

	// iterate thru each map in the file
	for (int y = 0; y < _areaHeight; y++) {
		for (int x = 0; x < _areaWidth; x++) {
			char mapFile[255];
			// get the path to the next map file
			fscanf_s(fileHandle, "%s ", mapFile, 255);

			cMap tempMap;
			// load the map
			if (tempMap.Load(mapFile) == false) {
				fclose(fileHandle);
				return false;
			}

			// set the map's tileset to the area's tileset
			tempMap.tileSet = _tileSet;
			// put the map in the area's map list
			mapList.push_back(tempMap);
		}
		fscanf_s(fileHandle, "\n");
	}
	fclose(fileHandle);

	return true;
}

///<summary>Renders the area to the destination surface at the given camera coordinates.</summary>
///<param name="dest">The destination SDL surface to render to.</param>
///<param name="cameraX">The x-coordinate of the camera.</param>
///<param name="cameraY">The y-coordinate of the camera.</param>
void cArea::Render(SDL_Surface *dest, int cameraX, int cameraY) {
	int firstId = ((-cameraY / _mapPixelHeight) * _areaHeight) + (-cameraX / _mapPixelWidth);

	for (int i = 0; i < 4; i++) {
		// based off the first id, determine the id of the next area to render
		unsigned int id = firstId + ((i / 2) * _areaWidth) + (i % 2);
		
		if (id < 0 || id >= mapList.size()) continue;

		// convert the map id into screen coordinates
		int x = ((id % _areaWidth) * _mapPixelWidth) + cameraX;
		int y = ((id / _areaWidth) * _mapPixelHeight) + cameraY;

		mapList[id].Render(dest, x, y);
	}
}

///<summary>Frees the tileset surface and clears the map list.</summary>
void cArea::UnLoad() {
	if (_tileSet) SDL_FreeSurface(_tileSet);
	_tileSet = 0;
	mapList.clear();
}

///<summary>Get the map that contains the given coordinates.</summary>
///<param name="x">The x-coordinate, in pixels.</param>
///<param name="y">The y-coordinate, in pixels.</param>
///<returns>Returns the map found at those coordinates, or null if not found.</returns>
cMap* cArea::GetMap(int x, int y) {
	unsigned int id = ((y / _mapPixelHeight) * _areaHeight) + (x / _mapPixelWidth);

	if (id < 0 || id >= mapList.size()) return 0;

	return &mapList[id];
}

///<summary>Get the tile that contains the given coordinates.</summary>
///<param name="x">The x-coordinate, in pixels.</param>
///<param name="y">The y-coordinate, in pixels.</param>
///<returns>Returns the tile found at those coordinates, or null if not found.</returns>
cTile* cArea::GetTile(int x, int y) {
	cMap* map = GetMap(x, y);

	if (map == 0) return 0;

	// the remainder of the coordinate divided by the map's width/height gives the pixel location relative 
	// to its top-left corner
	x = x % _mapPixelWidth;
	y = y % _mapPixelHeight;

	// get the tile from these relative coordinates
	return map->GetTile(x, y);
}