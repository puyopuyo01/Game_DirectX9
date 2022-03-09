#include"./SchemeBox.h"

SchemeBox::SchemeBox() {
	SchemeSE = new Sound("scheme.wav");
}

SchemeBox::~SchemeBox() {
	delete SchemeSE;
}

void SchemeBox::InsertScheme(Scheme* scheme) {
	schemelist.push_back(scheme);
}

StateInBattle* SchemeBox::Update(StateInBattle* nowState) {
	if ((int)schemelist.size() == 1) {
		SchemeSE->Reset();SchemeSE->Play(false);

		std::vector<Scheme*>::iterator itr = schemelist.begin();
		(*itr)->Excution();
		StateInBattle* next = new WaitingNextState(30, new InterputState(new InGame(), (*itr)->TextureNumber,(*itr)->name,(*itr)->intro));
		delete (*itr);
		schemelist.clear();
		return next;
	}
	else {
		/*必殺技ボタンを押したフレームが重なったらゲージのみ消費*/
		std::vector<Scheme*>::iterator itr = schemelist.begin();
		while (itr != schemelist.end()) {
			delete (*itr);
			itr++;
		}
		schemelist.clear();
		return nowState;
	}
}