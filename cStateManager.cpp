#include "cStateManager.h"

// Contructor.
cStateManager::cStateManager() {
}

// Destructor.
cStateManager::~cStateManager() {
	if (!_gameState.empty()) PopAll();
}

// Push a new game state object with the passed function pointer onto the stack.
bool cStateManager::Push(pStateFunc function) {
	if (function == 0) return false;

	// put the state function onto the stack
	_gameState.push(function);
	// initialize the new game state
	(*function)(INIT_PURPOSE);

	return true;
}

// Pop the current game state off of the stack and delete it from memory.
bool cStateManager::Pop() {
	if (_gameState.empty()) return false;

	// free up all resources held by the current game state
	pStateFunc state = _gameState.top();
	(*state)(STOP_PURPOSE);
	state = 0;
	// take the function off the stack
	_gameState.pop();

	return true;
}

// Remove all game state's from memory.
bool cStateManager::PopAll() {
	if (_gameState.empty()) return false;

	// remove all functions from the stack
	while (Pop()) {}

	return true;
}

// Process the current game state.
bool cStateManager::Process() {
	if (_gameState.empty()) return false;

	// run the current game state
	pStateFunc state = _gameState.top();
	(*state)(FRAME_PURPOSE);
	state = 0;

	return true;
}