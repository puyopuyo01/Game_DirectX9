#pragma once
#include"DXLib_Orig.h"


/*
‰æ–Ê‚ÌÀ•W‚ğfloatŒ^‚Åæ“¾‚·‚éŠÖ”ŒQ
áŠ±‚Ì‚¸‚ê‚ ‚èB
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