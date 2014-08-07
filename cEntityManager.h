#ifndef _CENTITYMANAGER_H_
#define _CENTITYMANAGER_H_

#include <vector>

#include "cEntity.h"

class cEntityCollision {
public:
	cEntityCollision();

	cEntity* A;
	cEntity* B;
};

class cEntityManager {
public:
	cEntityManager();
	~cEntityManager();
	void Update();
	void Render();
	void UnLoad();
	void ResolveCollisions();

	std::vector<cEntity*> entityList;
	std::vector<cEntityCollision> entityColList;
};

#endif