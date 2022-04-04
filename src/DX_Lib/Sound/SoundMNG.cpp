#include"./Sound.h"

unique_ptr<SoundMNG> SoundMNG::SingleTon;
vector<unique_ptr<Sound>> SoundMNG::sounds;

SoundMNG* SoundMNG::GetInstance() {
	if (SoundMNG::SingleTon == nullptr) { SoundMNG::SingleTon = make_unique<SoundMNG>(); }
	return SingleTon.get();
}

void SoundMNG::Release() {
	if (SingleTon != nullptr) {
		SingleTon->Init();
		SingleTon.reset();
	}
}

SoundMNG::SoundMNG() {
	Init();
}

void SoundMNG::Init() {
	sounds.clear();
	Sound_Identifier = 0;
}

/*音声を登録する。戻り値の値をGetSoundのIdentifierに指定すれば、音声を再生、停止することができる。*/

int SoundMNG::Regist_Sound(const char* file_name) {
	Sound_Identifier += 1;
	sounds.push_back(unique_ptr<Sound>(new Sound(file_name)));
	return Sound_Identifier;
}


void SoundMNG::Play(int Identifier,bool loop) {
	if (Identifier - 1 < 0) { return; }
	sounds[Identifier - 1]->Play(loop);

}

void SoundMNG::Stop(int Identifier) {
	if (Identifier - 1 < 0) { return; }
	sounds[Identifier - 1]->Stop();
}