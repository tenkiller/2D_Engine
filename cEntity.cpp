#include "cEntity.h"

std::vector<cEntity*> cEntity::entityList;
std::vector<cEntityCol> cEntity::entityColList;

cEntityCol::cEntityCol() {
	A = B = 0;
}

cEntity::cEntity() {
	x = 0.0f;
	y = 0.0f;
	width = 0;
	height = 0;
	moveLeft = false;
	moveRight = false;
	isDead = false;
	type = ENTITY_TYPE_GENERIC;
	flags = ENTITY_FLAG_NONE;
	maxSpeedX = 4;
	maxSpeedY = 10;
	accelRate = 1.0f;
	decelRate = 1.5f;
	_speedX = 0.0f;
	_speedY = 0.0f;
	_accelX = 0.0f;
	_accelY = 0.0f;
	_colX = 0;
	_colY = 0;
	_colWidth = 0;
	_colHeight = 0;
	_currentFrameCol = 0;
	_currentFrameRow = 0;
}

cEntity::~cEntity() {
	UnLoad();
}

///<summary>Load resources needed by the entity.</summary>
///<param name="file">The path and name of the graphic file to load.</param>
///<param name="w">Width in pixels.</param>
///<param name="h">Height in pixels.</param>
///<param name="maxFrames">Total number of frames.</param>
///<returns>Returns true if the operation is successful.</returns>
bool cEntity::Load(char* file, int w, int h, int maxFrames) {
	if ((_surface = cSurface::LoadFromFile(file)) == 0) return false;

	cSurface::Transparent(_surface, 255, 0, 255);

	width = w;
	height = h;
	_animControl.maxFrames = maxFrames;
	
	return true;
}

///<summary>Update paramters of the entity.</summary>
void cEntity::Update() {
	// if the entity isn't commanded to move, then stop
	if (moveLeft == false && moveRight == false) StopMove();

	if (moveLeft) _accelX = -accelRate;
	else if (moveRight) _accelX = accelRate;

	if (flags & ENTITY_FLAG_GRAVITY) {
		_accelY += GRAVITY;
		if (_accelY > GRAVITY) _accelY = GRAVITY;
	}

	// determine the number of pixels the entity is moving based off of the product of
	// the entity's velocity and computer's timing
	_speedX += _accelX * cFPS::FPSControl.GetSpeedFactor();
	_speedY += _accelY * cFPS::FPSControl.GetSpeedFactor();

	// cap the number of pixels the entity can move to its maximum allowed value
	if (_speedX >  maxSpeedX) _speedX = (float) maxSpeedX;
	if (_speedX < -maxSpeedX) _speedX = (float)-maxSpeedX;
	if (_speedY >  maxSpeedY) _speedY = (float) maxSpeedY;
	if (_speedY < -maxSpeedY) _speedY = (float)-maxSpeedY;

	Animate();
	Move(_speedX, _speedY);
}

///<summary>Render the entity to the destination surface.</summary>
///<param name="dest">Pointer to the destination surface.</param>
void cEntity::Render(SDL_Surface* dest) {
	if (dest == 0 || _surface == 0) return;

	cSurface::Draw(dest, _surface, 
				   (int)x - cCamera::cameraControl.GetX(), 
				   (int)y /*- cCamera::cameraControl.GetY()*/, 
				   _currentFrameCol * width, 
				   (_currentFrameRow + _animControl.GetCurrentFrame()) * height, 
				   width, height);
}

///<summary>Free memory allocated to the entity back to the operating system.</summary>
void cEntity::UnLoad() {
	if (_surface != 0) SDL_FreeSurface(_surface);
	_surface = 0;
}

///<summary>Animates the entity by cycling through its frames.</summary>
void cEntity::Animate() {
	// select the correct column of frames based on the direction of movement
	if (moveLeft) {
		_currentFrameCol = 0;
	} else if (moveRight) {
		_currentFrameCol = 1;
	}

	_animControl.Animate();
}

void cEntity::OnCollision(cEntity* entity) {
}

///<summary>Move the entity a number of pixels in both x and y directions, checking for collisions.</summary>
///<param name="moveX">The number of pixels to move in the x-direction.</param>
///<param name="moveY">The number of pixels to move in the y-direction.</param>
void cEntity::Move(float moveX, float moveY) {
	if (moveX == 0 && moveY == 0) return;

	float newX = 0.0f;
	float newY = 0.0f;
	
	// multiply moveX and moveY by the speed factor to get the correct movement per second
	moveX *= cFPS::FPSControl.GetSpeedFactor();
	moveY *= cFPS::FPSControl.GetSpeedFactor();

	// set how much we should inch closer to our desired position in the x-direction
	if (moveX != 0) {
		if (moveX >= 0) newX = cFPS::FPSControl.GetSpeedFactor();
		else newX = -cFPS::FPSControl.GetSpeedFactor();
	}

	// set how much we should inch closer to our desired position in the y-direction
	if (moveY != 0) {
		if (moveY >= 0) newY = cFPS::FPSControl.GetSpeedFactor();
		else newY = -cFPS::FPSControl.GetSpeedFactor();
	}

	while (true) {
		if (flags & ENTITY_FLAG_GHOST) {
			// check for collisions with other entities
			PosValid((int)(x + newX), (int)(y + newY));

			// inch x and y closer to our desired position
			x += newX;
			y += newY;
		} else {
			// check that movement in the horizontal direction is valid
			if (PosValid((int)(x + newX), (int)(y))) x += newX;
			else _speedX = 0;

			// check that movement in the vertical direction is valid
			if (PosValid((int)(x), (int)(y + newY))) y += newY;
			else _speedY = 0;
		}

		// decrease the distance to our desired position
		moveX += -newX;
		moveY += -newY;

		if (newX > 0 && moveX <= 0) newX = 0;
        if (newX < 0 && moveX >= 0) newX = 0;

        if (newY > 0 && moveY <= 0) newY = 0;
        if (newY < 0 && moveY >= 0) newY = 0;

        if (moveX == 0) newX = 0;
        if (moveY == 0) newY = 0;

		// if we reached our destination or a collision occurred, exit the loop
        if (moveX == 0 && moveY  == 0) break;
        if (newX  == 0 && newY   == 0) break;
	}
}

///<summary>Stops the entity if it's moving.</summary>
void cEntity::StopMove() {
	if (_speedX > 0) _accelX = -decelRate;
	if (_speedX < 0) _accelX = decelRate;

	if (_speedX < 2.0f && _speedX > -2.0f) {
		_accelX = 0;
		_speedX = 0;
	}
}

///<summary>Set the current frame of the entity.</summary>
void cEntity::JumpToFrame(int frame) {
	_animControl.JumpToFrame(frame);
}

///<summary>Determines if a collision with another entity has taken place.</summary>
///<param name="oX">The other entity's top-left x-coordinate.</param>
///<param name="oY">The other entity's top-left y-coordinate.</param>
///<param name="oW">The other entity's width, in pixels.</param>
///<param name="oH">The other entity's height, in pixels.</param>
///<returns>True if there is a collision with the other entity, false otherwise.</returns>
bool cEntity::Collides(int oX, int oY, int oW, int oH) {
	int left1, left2;
	int right1, right2;
	int top1, top2;
	int bottom1, bottom2;

	int tX = (int)x + _colX;
	int tY = (int)y + _colY;

	left1 = tX;
	left2 = oX;

	right1 = left1 + width - 1 - _colWidth;
	right2 = oX + oW - 1;

	top1 = tY;
	top2 = oY;

	bottom1 = top1 + height - 1 - _colHeight;
	bottom2 = oY + oH - 1;

	if (bottom1 < top2) return false;
	if (top1 > bottom2) return false;
	if (right1 < left2) return false;
	if (left1 > right2) return false;

	return true;
}

///<summary></summary>
///<param name="newX"></param>
///<param name="newY"></param>
///<returns></returns>
bool cEntity::PosValid(int newX, int newY) {
	// get the range of tiles the entity is moving across
	int startX = (newX + _colX) / TILE_SIZE;
	int startY = (newY + _colY) / TILE_SIZE;
	int endX = ((newX + _colX) + width - 1 - _colWidth) / TILE_SIZE;
	int endY = ((newY + _colY) + height - 1 - _colHeight) / TILE_SIZE;

	// iterate thru each tile the entity is moving thru and determine if there is a collision
	for (int y = startY; y <= endY; y++) {
		for (int x = startX; x <= endX; x++) {
			cTile* tile = cArea::areaControl.GetTile(x * TILE_SIZE, y * TILE_SIZE);
			//cTile* tile =  cMap::mapControl.GetTile(x * TILE_SIZE, y * TILE_SIZE);

			// check if the tile is a blocking tile
			if (PosValidTile(tile) == false) return false;
		}
	}

	// if the MAPONLY flag is ON, do not check entity collisions
	if (flags & ENTITY_FLAG_MAPONLY) {
	} else {
		// iterate thru each entity in the scene and determine if there was a collision
		for (unsigned int i = 0; i < entityList.size(); i++) {
			if (PosValidEntity(entityList[i], newX, newY) == false) return false;
		}
	}
	return true;
}

///<summary></summary>
///<param name="tile"></param>
///<returns></returns>
bool cEntity::PosValidTile(cTile* tile) {
	if (tile == 0) return true;

	if (tile->typeID == TILE_TYPE_BLOCK) return false;

	return true;
}

///<summary></summary>
///<param name="entity"></param>
///<param name="newY"></param>
///<param name="newY"></param>
///<returns></returns>
bool cEntity::PosValidEntity(cEntity *entity, int newX, int newY) {
	if (this != entity && 
		entity != 0 && 
		!entity->isDead && 
		entity->flags ^ ENTITY_FLAG_MAPONLY &&
		entity->Collides(newX + _colX, newY + _colY, width - 1 - _colWidth, height - 1 - _colHeight)) {
			cEntityCol entityCol;

			entityCol.A = this;
			entityCol.B = entity;

			entityColList.push_back(entityCol);
			return false;
	}
	return true;
}
