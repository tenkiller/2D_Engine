#include "cApp.h"

///<summary>Handles event messages raised by the user or application.</summary>
///<param name="Event">Pointer to the SDL_Event structure which contains details about the event.</param>
void cApp::OnEvent(SDL_Event* Event) {
	// pass all events to the top screen
	_screenManager->OnEvent(Event);
	// handle any events not handled by the top screen
	cEvent::OnEvent(Event);
}

///<summary>Sets the flag indicating the application is closing.</summary>
void cApp::OnExit() {
	_running = false;
}