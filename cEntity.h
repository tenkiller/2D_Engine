#ifndef _CENTITY_H_
#define _CENTITY_H_

#include "cAnimation.h"
#include "cSurface.h"
#include "cFPS.h"
#include "cArea.h"
#include "cCamera.h"

enum eEntityType {
	ENTITY_TYPE_PLAYER	= 0,
	ENTITY_TYPE_GENERIC
};

enum eEntityFlags {
	ENTITY_FLAG_NONE	= 0,
	ENTITY_FLAG_GRAVITY	= 0x00000001,
	ENTITY_FLAG_GHOST	= 0x00000002,
	ENTITY_FLAG_MAPONLY	= 0x00000004
};

class cEntityCol;

class cEntity {
public:
	cEntity();
	virtual ~cEntity();
	virtual bool Load(char* file, int w, int h, int maxFrames);
	virtual void Update();
	virtual void Render(SDL_Surface* dest);
	virtual void UnLoad();
	virtual void Animate();
	void Move(float moveX, float moveY);
	void StopMove();
	void JumpToFrame(int frame);

	virtual void OnCollision(cEntity* entity);
	bool Collides(int oX, int oY, int oW, int oH);
	bool PosValid(int newX, int newY);
	bool PosValidTile(cTile* tile);
	bool PosValidEntity(cEntity* entity, int newX, int newY);

	float x;
	float y;
	int width;
	int height;

	bool moveLeft;
	bool moveRight;
	bool isDead;

	int type;									// the type of entity
	int flags;									// the flags set for this entity

	int maxSpeedX;								// maximum speed to move in the x-direction
	int maxSpeedY;								// maximum speed to move in the y-direction
	float accelRate;							// the rate of acceleration for moving
	float decelRate;							// the rate of deceleration for stopping

	static std::vector<cEntity*> entityList;
	static std::vector<cEntityCol> entityColList;

protected:
	cAnimation _animControl;					// the animation controller
	SDL_Surface* _surface;						// the surface containing the animation frames

	int _currentFrameCol;						// the column of frames to use for the current animation
	int _currentFrameRow;						// the row of frames to use for the current animation

	float _speedX;								// speed in the x-direction (number of pixels to move entity)
	float _speedY;								// speed in the y-direction (number of pixels to move entity)
	float _accelX;								// acceleration in the x-direction (pixels to move per cycle)
	float _accelY;								// acceleration in the y-direction (pixels to move per cycle)

	int _colX;									// x-offset for collisions
	int _colY;									// y-offset for collisions
	int _colWidth;								// width offset for collisions
	int _colHeight;								// height offset for collisions
};

class cEntityCol {
public:
	cEntityCol();

	cEntity* A;
	cEntity* B;
};

#endif