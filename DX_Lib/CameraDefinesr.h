#pragma once
#include"DXLib_Orig.h"
#define CAMERA_Z -100.f


float GetScreenX() {
	return -CAMERA_Z*std::tan(D3DXToRadian(45.0f / 2.f));
}

