#pragma once
#include"DX_Lib/DXLib_Orig.h"
#include"DX_Lib/Image/FileMapping.h"




/*音声処理クラス*/
class Sound {
public:
	Sound(const char* file);
	~Sound();
	void Play(bool loop); /*音を再生する関数。引数でループするかを指定*/
	void Reset(); /*音を始めからにする関数。*/
	void Stop();

	void Release();

	LPDIRECTSOUNDBUFFER Secondary;
	
};


class SoundMNG {
public:
	static SoundMNG* GetInstance();
	static void Release();

	SoundMNG();
	void Init();
	int Regist_Sound(const char* file_name);

	void Play(int Identifier, bool loop);
	void Stop(int Identifier);
private:
	static unique_ptr<SoundMNG> SingleTon;
	static vector<unique_ptr<Sound>> sounds;
	int Sound_Identifier;
};