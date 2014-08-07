#ifndef _CPROCESSMANAGER_H_
#define _CPROCESSMANAGER_H_

#include <map>

typedef void (*pProcessFunc)();

class cProcessManager {
public:
	cProcessManager();
	~cProcessManager();
	int Push(pProcessFunc);
	bool Pop(unsigned int id);
	bool PopAll();
	bool Process();

private:
	unsigned int _processCount;
	std::map<unsigned int, pProcessFunc> _gameProcess;
};

#endif