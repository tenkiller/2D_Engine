#ifndef _CAPP_H_
#define _CAPP_H_

#include <string>
#include <iostream>

#include "SDL.h"
#include "globals.h"
#include "cEvent.h"
#include "cPlayer.h"
#include "cScreenManager.h"
#include "cBackgroundScreen.h"
#include "cGameScreen.h"

class cApp : public cEvent {
public:
	cApp();
	bool Init();
	int Run();
	void Update();
	void Render();
	void ShutDown();
	//void ResizeWindow(int w, int h);
	//void ToggleFullScreen();
	void OnEvent(SDL_Event* Event);
	void OnExit();

private:
	int _width;							// width of the screen in pixels
	int _height;						// height of the screen in pixels
	int _bpp;							// the number of bits per pixel
	bool _fullScreen;					// true if the application is fullscreen; false if a window
	std::string _strWindowName;			// the title of the window
	SDL_Surface* _screen;				// the display screen
	Uint32 _SDLFlags;					// SDL setup flags
	bool _running;						// true if the application is running; false otherwise

	cScreenManager* _screenManager;		// manages all screens in the application
	cGameScreen _gameScreen;			// the screen where the game is played
};

#endif