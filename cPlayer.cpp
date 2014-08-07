#include "cPlayer.h"

cPlayer::cPlayer() {
	jump = false;
	_jumpAccel = 0.0f;
}

bool cPlayer::Load(char* file, int w, int h, int maxFrames) {
	if (cEntity::Load(file, w, h, maxFrames) == false) return false;
	
	type = ENTITY_TYPE_PLAYER;		// player flag
	flags = ENTITY_FLAG_GRAVITY;	// affected by gravity

	_colX = 20;						// collision x-offset
	_colWidth = 39;					// collision width offset

	// precompute jump acceleration
	_jumpAccel = -(float)(sqrt(3.8f * GRAVITY * height));

	return true;
}

void cPlayer::Update() {
	// allow the player to jump, but only if they're on the ground
	if (jump && _speedY == 0) {
		_accelY = _jumpAccel;
		jump = false;
	}

	cEntity::Update();
}

void cPlayer::Render(SDL_Surface* dest) {
	cEntity::Render(dest);
}

void cPlayer::UnLoad() {
	cEntity::UnLoad();
}

void cPlayer::Animate() {
	// if the player isn't moving, then stop the movement animation
	if (_speedX != 0) _animControl.maxFrames = 8;
	else _animControl.maxFrames = 0;

	if (jump) _animControl.JumpToFrame(2);

	cEntity::Animate();
}

void cPlayer::OnCollision(cEntity* entity) {
	if (entity == 0) return;
}

void cPlayer::Pain(cEntity *source, int amount) {
	if (source == 0) return;
}