#pragma once
#include"DX_Lib/DXLib_Orig.h"
#include"DX_Lib/Image/FileMapping.h"




/*���������N���X*/
class Sound {
public:
	Sound(const char* file);
	~Sound();
	void Play(bool loop); /*�����Đ�����֐��B�����Ń��[�v���邩���w��*/
	void Reset(); /*�����n�߂���ɂ���֐��B*/
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