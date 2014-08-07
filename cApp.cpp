#include "cApp.h"

cApp::cApp() {
	_width = 0;
	_height = 0;
	_bpp = 0;
	_fullScreen = false;
	_strWindowName = "";
	_screen = 0;
	_SDLFlags = 0;
	_running = true;
}

///<summary>Starts the application game loop.</summary>
///<returns>Returns 0 if the operation is successful; -1 if there is an error.</returns>
int cApp::Run() {
	if (!Init()) return -1;

	SDL_Event Event;

	while (_running) {
		while (SDL_PollEvent(&Event)) { OnEvent(&Event); }
		Update();
		Render();
	}

	ShutDown();
	return 0;
}

///<summary>Releases memory used by the application back to the operating system.</summary>
void cApp::ShutDown() {
	SDL_FreeSurface(_screen);
	SDL_Quit();
}

///<summary>Program entry point.</summary>
///<param name="argc"></param>
///<param name="argv"></param>
///<returns>Returns 0 if the operation is successful; -1 if there is an error.</returns>
int main(int argc, char* argv[]) {
	cApp app;

	return app.Run();
}