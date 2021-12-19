#include"./SchemeBox.h"

void SchemeBox::InsertScheme(Scheme* scheme) {
	schemelist.push_back(scheme);
}

StateInBattle* SchemeBox::Update(StateInBattle* nowState) {
	if ((int)schemelist.size() == 1) {
		std::vector<Scheme*>::iterator itr = schemelist.begin();
		(*itr)->Excution();

		StateInBattle* next = new WaitingNextState(30, new InterputState(new InGame(), (*itr)->TextureNumber,(*itr)->name,(*itr)->intro));
		delete (*itr);
		schemelist.clear();
		return next;
	}
	else {
		std::vector<Scheme*>::iterator itr = schemelist.begin();
		while (itr != schemelist.end()) {
			delete (*itr);
			itr++;
		}
		schemelist.clear();
		return nowState;
	}
}