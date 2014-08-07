#include "cEntityManager.h"

cEntityManager::cEntityManager() {
	entityList.clear();
	entityColList.clear();
}

cEntityManager::~cEntityManager() {
	UnLoad();
}

void cEntityManager::Update() {
	std::vector<cEntity*>::iterator iter;

	for (iter = entityList.begin(); iter != entityList.end(); iter++) {
		(*iter)->Update();
	}
}

void cEntityManager::Render() {
	std::vector<cEntity*>::iterator iter;

	/*for (iter = entityList.begin(); iter != entityList.end(); iter++) {
		(*iter)->Render();
	}*/
}

void cEntityManager::UnLoad() {
	if (!entityList.empty()) {
		std::vector<cEntity*>::iterator iter;

		for (iter = entityList.begin(); iter != entityList.end(); iter++) {
			(*iter)->UnLoad();
		}
	}

	entityColList.clear();
}

void cEntityManager::ResolveCollisions() {
	std::vector<cEntityCollision>::iterator iter;

	for (iter = entityColList.begin(); iter != entityColList.end(); iter++) {
		(*iter).A->OnCollision((*iter).B);
		(*iter).B->OnCollision((*iter).A);
	}
}