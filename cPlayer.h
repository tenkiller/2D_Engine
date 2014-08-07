#ifndef _CPLAYER_H_
#define _CPLAYER_H_

#include <cmath>

#include "cEntity.h"

class cPlayer : public cEntity {
public:
	cPlayer();
	bool Load(char* file, int w, int h, int maxFrames);
	void Update();
	void Render(SDL_Surface* dest);
	void UnLoad();
	void Animate();
	void OnCollision(cEntity* entity);

	void Pain(cEntity* source, int amount);

	bool jump;

private:
	float _jumpAccel;
};

#endif