#pragma once
#include"DX_Lib/DXLib_Orig.h"
#include"DX_Lib/Image/FileMapping.h"




/*���������N���X*/
class Sound {
public:
	Sound(const char* file);
	~Sound();
	void Release(); /*�������֐��B*/
	void Play(bool loop); /*�����Đ�����֐��B�����Ń��[�v���邩���w��*/
	void Reset(); /*�����n�߂���ɂ���֐��B*/
	void Stop();
private:
	LPDIRECTSOUNDBUFFER Secondary;
};