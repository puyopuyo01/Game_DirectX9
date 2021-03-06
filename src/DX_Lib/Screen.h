#pragma once
#include"DXLib_Orig.h"


/*
画面の座標をfloat型で取得する関数群
若干のずれあり。
*/

extern const float CAMERA_X;
extern const float CAMERA_Y;
extern const float CAMERA_Z;

extern const DWORD CLIENT_WIDTH;
extern const DWORD CLIENT_HEIGHT;

void SetAspect();

float ScreenLX();
float ScreenRX();
float ScreenUpperY();
float ScreenLowerY();

float ScreenCenterX();
float ScreenCenterY();

float ScreenWidth();
float ScreenHeigth();

void SetScreenSize(float* x, float* y, float* width, float* height);