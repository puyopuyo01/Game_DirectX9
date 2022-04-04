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

/*������o�^����B�߂�l�̒l��GetSound��Identifier�Ɏw�肷��΁A�������Đ��A��~���邱�Ƃ��ł���B*/

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