#include "cGameScreen.h"

cGameScreen::cGameScreen() {
}

bool cGameScreen::Load() {
	cArea::areaControl.Load("./areas/testArea.area");

	_yoshi.Load("./gfx/yoshi.bmp", 64, 64, 8);
	//_yoshi.x = (float)(WINDOW_WIDTH / 2);
	_yoshi.y = (float)(WINDOW_HEIGHT - _yoshi.height - (TILE_SIZE * 5) - 1);

	cEntity::entityList.push_back(&_yoshi);

	cCamera::cameraControl.targetMode = TARGET_MODE_CENTER;
	cCamera::cameraControl.SetTarget(&_yoshi.x, &_yoshi.y);

	return true;
}

void cGameScreen::Update() {
	std::vector<cEntity*>::iterator iter;
	for (iter = cEntity::entityList.begin(); iter != cEntity::entityList.end(); iter++) {
		(*iter)->Update();
	}
}

void cGameScreen::Render(SDL_Surface* dest) {
	cArea::areaControl.Render(dest, -cCamera::cameraControl.GetX(), 0);
	//cMap::mapControl.Render(dest, 0, 0);
	std::vector<cEntity*>::iterator iter;
	for (iter = cEntity::entityList.begin(); iter != cEntity::entityList.end(); iter++) {
		(*iter)->Render(dest);
	}
}

void cGameScreen::UnLoad() {
	std::vector<cEntity*>::iterator iter;
	for (iter = cEntity::entityList.begin(); iter != cEntity::entityList.end(); iter++) {
		(*iter)->UnLoad();
	}

	cArea::areaControl.UnLoad();
	//cMap::mapControl.tileSet = 0;

	cScreen::UnLoad();
}

void cGameScreen::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
	switch (sym) {
		case SDLK_LEFT:
			_yoshi.moveLeft = true;
			break;
		case SDLK_RIGHT:
			_yoshi.moveRight = true;
			break;
		case SDLK_SPACE:
			_yoshi.jump = true;
			break;
		default:
			break;
	}
}

void cGameScreen::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
	switch (sym) {
		case SDLK_LEFT:
			_yoshi.moveLeft = false;
			break;
		case SDLK_RIGHT:
			_yoshi.moveRight = false;
			break;
		case SDLK_SPACE:
			_yoshi.jump = false;
			break;
		default:
			break;
	}
}