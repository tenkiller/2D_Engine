#ifndef _CSTATEMANAGER_H_
#define _CSTATEMANAGER_H_

#include <stack>

// Used to tell a state function why it was called.
enum ePurpose {
	STOP_PURPOSE = 0,
	INIT_PURPOSE,
	FRAME_PURPOSE,
	NO_PURPOSE
};

typedef void (*pStateFunc)(ePurpose);

class cStateManager {
public:
	cStateManager();
	~cStateManager();
	bool Push(pStateFunc);
	bool Pop();
	bool PopAll();
	bool Process();

private:
	std::stack<pStateFunc> _gameState;
};

#endif