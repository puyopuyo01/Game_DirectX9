#pragma once
#include"DX_Lib/DXLib_Orig.h"
#include"DX_Lib/Image/FileMapping.h"




/*音声処理クラス*/
class Sound {
public:
	Sound(const char* file);
	~Sound();
	void Release(); /*解放する関数。*/
	void Play(bool loop); /*音を再生する関数。引数でループするかを指定*/
	void Reset(); /*音を始めからにする関数。*/
	void Stop();
private:
	LPDIRECTSOUNDBUFFER Secondary;
};