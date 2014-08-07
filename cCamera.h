#ifndef _CCAMERA_H_
#define _CCAMERA_H_

#include "globals.h"

enum eCameraTargetModes {
	TARGET_MODE_NORMAL = 0,
	TARGET_MODE_CENTER
};

class cCamera {
public:
	cCamera();
	void Move(int moveX, int moveY);
	int GetX();
	int GetY();
	void SetPos(int x, int y);
	void SetTarget(float* x, float* y);

public:
	int targetMode;

private:
	int x;
	int y;
	float* targetX;
	float* targetY;

public:
	static cCamera cameraControl;
};

#endif