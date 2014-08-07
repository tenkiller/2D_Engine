#include "cSurface.h"

cSurface::cSurface() {
}

///<summary>Creates an SDL surface from a graphic file.</summary>
///<param name="file">The path and name of the graphic file to load.</param>
///<returns>A pointer to the created SDL_Surface.</returns>
SDL_Surface* cSurface::LoadFromFile(char *file) {
	SDL_Surface* temp = 0;
	SDL_Surface* image = 0;

	if ((temp = SDL_LoadBMP(file)) == 0) return 0;

	image = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	return image;
}

///<summary>Draws an SDL source onto another SDL surface.</summary>
///<param name="dest">The destination SDL surface.</param>
///<param name="src">The source SDL surface.</param>
///<param name="x">The x-coordinate to draw to on the destination surface.</param>
///<param name="y">The y-coordinate to draw to on the destination surface.</param>
///<returns>Returns true if the operation is successful.</returns>
bool cSurface::Draw(SDL_Surface *dest, SDL_Surface *src, int x, int y) {
	if (dest == 0 || src == 0) return false;

	SDL_Rect destRect;

	destRect.x = x;
	destRect.y = y;

	SDL_BlitSurface(src, NULL, dest, &destRect);

	return true;
}

///<summary>Draws an SDL source onto another SDL surface.</summary>
///<param name="dest">The destination SDL surface.</param>
///<param name="src">The source SDL surface.</param>
///<param name="destX">The x-coordinate to draw to on the destination surface.</param>
///<param name="destY">The y-coordinate to draw to on the destination surface.</param>
///<param name="srcX">The x-coordinate to read from the source surface.</param>
///<param name="srcY">The y-coordinate to read from the source surface.</param>
///<param name="w">The width of the source surface.</param>
///<param name="h">The height of the source surface.</param>
///<returns>Returns true if the operation is successful.</returns>
bool cSurface::Draw(SDL_Surface *dest, SDL_Surface *src, int destX, int destY, int srcX, int srcY, int w, int h) {
	if (dest == 0 || src == 0) return false;

	SDL_Rect srcRect;

	srcRect.x = srcX;
	srcRect.y = srcY;
	srcRect.w = w;
	srcRect.h = h;

	SDL_Rect destRect;

	destRect.x = destX;
	destRect.y = destY;

	SDL_BlitSurface(src, &srcRect, dest, &destRect);

	return true;
}

///<summary>Sets the specified color on the given SDL surface as transparent.</summary>
///<param name="dest">The SDL surface.</param>
///<param name="r">The red color value.</param>
///<param name="g">The green color value.</param>
///<param name="b">The blue color value.</param>
///<returns>Returns true if the operation is successful.</returns>
bool cSurface::Transparent(SDL_Surface *dest, int r, int g, int b) {
	if (dest == 0) return false;

	SDL_SetColorKey(dest, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(dest->format, r, g, b));

	return true;
}