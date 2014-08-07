#include "cApp.h"

///<summary>Initializes all assets and resources used by the application.</summary>
///<returns>Returns true if the operation is successful.</returns>
bool cApp::Init() {

	#pragma region SDL SetUp

	// intialize video properties
	_width = WINDOW_WIDTH;
	_height = WINDOW_HEIGHT;
	_bpp = 32;
	_strWindowName = "SDL 2D Engine v0.1";
	_SDLFlags = SDL_HWSURFACE | SDL_DOUBLEBUF;

	// intialize SDL
	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0) return false;
	// get a reference to the game screen
	if ((_screen = SDL_SetVideoMode(_width, _height, _bpp, _SDLFlags)) == 0) return false;
	
	// change the window title
	SDL_WM_SetCaption(_strWindowName.c_str(), 0);
	// enable key repeating
	//SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

	#pragma endregion

	#pragma region Screen Management

	// create the screen manager
	_screenManager = new cScreenManager(_screen);
	// push the background (black) screen onto the stack
	_screenManager->Push(new cBackgroundScreen);

	// set up the game screen
	_gameScreen.Load();
	_gameScreen.active = true;
	_gameScreen.SetScreenManager(_screenManager);
	_screenManager->Push(&_gameScreen);	

	#pragma endregion

	return true;
}