#pragma once
#include<Windows.h>
#include<stdio.h>
#include<timeapi.h>
#include"Array.h"
#include"DX_Lib/Screen.h"
#pragma comment(lib,"winmm.lib")

/*FPS�����N���X
 60fps�ŌŒ肷��
*/

class Font;

class FPS {
public:
	static FPS* GetInstance();
	void InitFPS();
	void ReleaseFPS();
	void SMesure();
	void Measure();

	void Draw();
private:
	Array* averageFPS;
	LARGE_INTEGER startTime;
	LARGE_INTEGER Freq;


	Font* Text;
	static FPS* SingleTon;
	float fps;
};