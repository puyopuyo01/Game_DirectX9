#include"./SchemeBox.h"

int SchemeBox::SchemeSE;

SchemeBox::SchemeBox() {
	printf("SchemeBoxt\n");
}

SchemeBox::~SchemeBox() {
	printf("SchemeBoxDest\n");
}

void SchemeBox::InsertScheme(Scheme* scheme) {
	schemelist.push_back(unique_ptr<Scheme>(std::move(scheme)));
}

StateInBattle* SchemeBox::Update(StateInBattle* nowState) {
	/*�K�E�Z�{�^�����������t���[�����d�Ȃ�����Q�[�W�̂ݏ���*/
	if ((int)schemelist.size() == 1) {
		SoundMNG::GetInstance()->Play(SchemeSE,false);
		std::vector<unique_ptr<Scheme>>::iterator itr = schemelist.begin();
		(*itr)->Excution();
		StateInBattle* next = new WaitingNextState(30, new InterputState(new InGame(), (*itr)->TextureNumber,(*itr)->name,(*itr)->intro));
		schemelist.clear();
		return next;
	}
	else{
		schemelist.clear();
		return nowState;
	}
}

void SchemeBox::LoadSound() {
	SchemeSE = SoundMNG::GetInstance()->Regist_Sound("scheme.wav");
}