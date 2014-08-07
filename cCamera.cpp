#include "cCamera.h"

cCamera cCamera::cameraControl;

cCamera::cCamera() {
	x = 0;
	y = 0;
	targetX = 0;
	targetY = 0;
	targetMode = TARGET_MODE_NORMAL;
}

///<summary>Move the camera by the specified number of pixels.</summary>
///<param name="moveX">The number of pixels to move the camera along the x-axis.</param>
///<param name="moveY">The number of pixels to move the camera along the y-axis.</param>
void cCamera::Move(int moveX, int moveY) {
	x += moveX;
	y += moveY;
}

///<summary>Get the x-position of the camera.</summary>
///<returns>Returns the x-position of the camera.</returns>
int cCamera::GetX() {
	if (targetX != 0) {
		if (targetMode == TARGET_MODE_CENTER) {
			return (int)(*targetX - (WINDOW_WIDTH / 2));
		}
		return (int)*targetX;
	}
	return x;
}

///<summary>Get the y-position of the camera.</summary>
///<returns>Returns the y-position of the camera.</returns>
int cCamera::GetY() {
	if (targetY != 0) {
		if (targetMode == TARGET_MODE_CENTER) {
			return (int)(*targetY - (WINDOW_HEIGHT / 2));
		}
		return (int)*targetY;
	}
	return y;
}

///<summary>Sets the position of the camera.</summary>
///<param name="x">The x-coordinate of the camera.</param>
///<param name="y">The y-coordinate of the camera.</param>
void cCamera::SetPos(int x, int y) {
	this->x = x;
	this->y = y;
}

///<summary>Sets the position on the target for the camera to track.</summary>
///<param name="x">The x-coordinate on the target.</param>
///<param name="y">The y-coordinate on the target.</param>
void cCamera::SetTarget(float *x, float *y) {
	targetX = x;
	targetY = y;
}