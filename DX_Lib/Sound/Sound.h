#pragma once
#include"DX_Lib/DXLib_Orig.h"
#include"DX_Lib/Image/FileMapping.h"


/*���������N���X*/
class Sound {
public:
	Sound(const char* file);
	~Sound();
	void Release();
	void Play(bool loop);
	void Reset();
private:
	LPDIRECTSOUNDBUFFER Secondary;
};


class BGM:public Sound{
};


class SE:public Sound{};