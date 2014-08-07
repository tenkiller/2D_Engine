#include "cProcessManager.h"

// Constructor.
cProcessManager::cProcessManager() {
	_processCount = 0;
}

// Destructor.
cProcessManager::~cProcessManager() {
	if (!_gameProcess.empty()) _gameProcess.clear();
}

// Pushes a process function into the class' container.
int cProcessManager::Push(pProcessFunc function) {
	if (function == 0) return 0;

	// place the process function into the container
	_gameProcess[++_processCount] = function;

	// initialize the new game process
	//(*function)();

	return _processCount;
}

// Erases the process from the class container based on the given id.
bool cProcessManager::Pop(unsigned int id) {
	if (_gameProcess.empty() || id < 1) return false;

	//pProcessFunc process;

	// find the process function in the container from its process id
	//if ((process = _gameProcess.find(id)->second) == 0) return false;
	// free up all resources held by the game process
	//(*process)()

	// remove the game process from the container
	if (_gameProcess.erase(id) > 0) return true;

	return false;
}

// Clears all the processes from the class container.
bool cProcessManager::PopAll() {
	if (_gameProcess.empty()) return false;

	// remove all process functions from the container
	_gameProcess.clear();

	return true;
}

// Runs all game processes stored in the class container.
bool cProcessManager::Process() {
	if (_gameProcess.empty()) return false;

	std::map<unsigned int, pProcessFunc>::iterator iter;

	// run all game processes in the container
	for (iter = _gameProcess.begin(); iter != _gameProcess.end(); iter++) {
		pProcessFunc process = iter->second;
		(*process)();
	}

	return true;
}